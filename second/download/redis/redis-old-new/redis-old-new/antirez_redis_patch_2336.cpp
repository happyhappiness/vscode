@@ -3013,9 +3013,6 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
         /* If we have a target key where to store the resulting set
          * create this key with an empty set inside */
         dstset = createSetObject();
-        deleteKey(c->db,dstkey);
-        dictAdd(c->db->dict,dstkey,dstset);
-        incrRefCount(dstkey);
     }
 
     /* Iterate all the elements of the first (smallest) set, and test
@@ -3044,6 +3041,13 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
     }
     dictReleaseIterator(di);
 
+    if (dstkey) {
+        /* Store the resulting set into the target */
+        deleteKey(c->db,dstkey);
+        dictAdd(c->db->dict,dstkey,dstset);
+        incrRefCount(dstkey);
+    }
+
     if (!dstkey) {
         lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
     } else {
@@ -3095,20 +3099,6 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
      * this set object will be the resulting object to set into the target key*/
     dstset = createSetObject();
 
-    /* The first thing we should output is the total number of elements...
-     * since this is a multi-bulk write, but at this stage we don't know
-     * the intersection set size, so we use a trick, append an empty object
-     * to the output list and save the pointer to later modify it with the
-     * right length */
-    if (dstkey) {
-        /* If we have a target key where to store the resulting set
-         * create this key with an empty set inside */
-        deleteKey(c->db,dstkey);
-        dictAdd(c->db->dict,dstkey,dstset);
-        incrRefCount(dstkey);
-        server.dirty++;
-    }
-
     /* Iterate all the elements of all the sets, add every element a single
      * time to the result set */
     for (j = 0; j < setsnum; j++) {
@@ -3154,6 +3144,13 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
             addReply(c,shared.crlf);
         }
         dictReleaseIterator(di);
+    } else {
+        /* If we have a target key where to store the resulting set
+         * create this key with the result set inside */
+        deleteKey(c->db,dstkey);
+        dictAdd(c->db->dict,dstkey,dstset);
+        incrRefCount(dstkey);
+        server.dirty++;
     }
 
     /* Cleanup */
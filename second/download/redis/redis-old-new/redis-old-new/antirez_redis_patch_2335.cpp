@@ -721,7 +721,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     }
 
     /* Close connections of timedout clients */
-    if (!(loops % 10))
+    if (server.maxidletime && !(loops % 10))
         closeTimedoutClients();
 
     /* Check if a background saving in progress terminated */
@@ -960,7 +960,7 @@ static void loadServerConfig(char *filename) {
         /* Execute config directives */
         if (!strcasecmp(argv[0],"timeout") && argc == 2) {
             server.maxidletime = atoi(argv[1]);
-            if (server.maxidletime < 1) {
+            if (server.maxidletime < 0) {
                 err = "Invalid timeout value"; goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"port") && argc == 2) {
@@ -3014,9 +3014,6 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
         /* If we have a target key where to store the resulting set
          * create this key with an empty set inside */
         dstset = createSetObject();
-        deleteKey(c->db,dstkey);
-        dictAdd(c->db->dict,dstkey,dstset);
-        incrRefCount(dstkey);
     }
 
     /* Iterate all the elements of the first (smallest) set, and test
@@ -3045,6 +3042,13 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
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
@@ -3096,23 +3100,10 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
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
+        if (op == REDIS_OP_DIFF && j == 0 && !dv[j]) break; /* result set is empty */
         if (!dv[j]) continue; /* non existing keys are like empty sets */
 
         di = dictGetIterator(dv[j]);
@@ -3135,6 +3126,8 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
             }
         }
         dictReleaseIterator(di);
+
+        if (op == REDIS_OP_DIFF && cardinality == 0) break; /* result set is empty */
     }
 
     /* Output the content of the resulting set, if not in STORE mode */
@@ -3152,6 +3145,13 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
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
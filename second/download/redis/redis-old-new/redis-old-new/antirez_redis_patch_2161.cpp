@@ -4373,6 +4373,7 @@ static void popGenericCommand(redisClient *c, int where) {
         robj *ele = listNodeValue(ln);
         addReplyBulk(c,ele);
         listDelNode(list,ln);
+        if (listLength(list) == 0) deleteKey(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -4465,6 +4466,7 @@ static void ltrimCommand(redisClient *c) {
         ln = listLast(list);
         listDelNode(list,ln);
     }
+    if (listLength(list) == 0) deleteKey(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.ok);
 }
@@ -4498,6 +4500,7 @@ static void lremCommand(redisClient *c) {
         }
         ln = next;
     }
+    if (listLength(list) == 0) deleteKey(c->db,c->argv[1]);
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
 }
 
@@ -4557,6 +4560,7 @@ static void rpoplpushcommand(redisClient *c) {
 
         /* Finally remove the element from the source list */
         listDelNode(srclist,ln);
+        if (listLength(srclist) == 0) deleteKey(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -4595,6 +4599,7 @@ static void sremCommand(redisClient *c) {
     if (dictDelete(set->ptr,c->argv[2]) == DICT_OK) {
         server.dirty++;
         if (htNeedsResize(set->ptr)) dictResize(set->ptr);
+        if (dictSize((dict*)set->ptr) == 0) deleteKey(c->db,c->argv[1]);
         addReply(c,shared.cone);
     } else {
         addReply(c,shared.czero);
@@ -4624,6 +4629,8 @@ static void smoveCommand(redisClient *c) {
         addReply(c,shared.czero);
         return;
     }
+    if (dictSize((dict*)srcset->ptr) == 0 && srcset != dstset)
+        deleteKey(c->db,c->argv[1]);
     server.dirty++;
     /* Add the element to the destination set */
     if (!dstset) {
@@ -4675,6 +4682,7 @@ static void spopCommand(redisClient *c) {
         addReplyBulk(c,ele);
         dictDelete(set->ptr,ele);
         if (htNeedsResize(set->ptr)) dictResize(set->ptr);
+        if (dictSize((dict*)set->ptr) == 0) deleteKey(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -4776,10 +4784,15 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long
     dictReleaseIterator(di);
 
     if (dstkey) {
-        /* Store the resulting set into the target */
+        /* Store the resulting set into the target, if the intersection
+         * is not an empty set. */
         deleteKey(c->db,dstkey);
-        dictAdd(c->db->dict,dstkey,dstset);
-        incrRefCount(dstkey);
+        if (dictSize((dict*)dstset->ptr) > 0) {
+            dictAdd(c->db->dict,dstkey,dstset);
+            incrRefCount(dstkey);
+        } else {
+            decrRefCount(dstset);
+        }
     }
 
     if (!dstkey) {
@@ -4878,8 +4891,12 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
         /* If we have a target key where to store the resulting set
          * create this key with the result set inside */
         deleteKey(c->db,dstkey);
-        dictAdd(c->db->dict,dstkey,dstset);
-        incrRefCount(dstkey);
+        if (dictSize((dict*)dstset->ptr) > 0) {
+            dictAdd(c->db->dict,dstkey,dstset);
+            incrRefCount(dstkey);
+        } else {
+            decrRefCount(dstset);
+        }
     }
 
     /* Cleanup */
@@ -5339,6 +5356,7 @@ static void zremCommand(redisClient *c) {
     /* Delete from the hash table */
     dictDelete(zs->dict,c->argv[2]);
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+    if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.cone);
 }
@@ -5356,6 +5374,7 @@ static void zremrangebyscoreCommand(redisClient *c) {
     zs = zsetobj->ptr;
     deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+    if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
     server.dirty += deleted;
     addReplyLong(c,deleted);
 }
@@ -5390,6 +5409,7 @@ static void zremrangebyrankCommand(redisClient *c) {
      * use 1-based rank */
     deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+    if (dictSize(zs->dict) == 0) deleteKey(c->db,c->argv[1]);
     server.dirty += deleted;
     addReplyLong(c, deleted);
 }
@@ -5573,11 +5593,15 @@ static void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
     }
 
     deleteKey(c->db,dstkey);
-    dictAdd(c->db->dict,dstkey,dstobj);
-    incrRefCount(dstkey);
-
-    addReplyLong(c, dstzset->zsl->length);
-    server.dirty++;
+    if (dstzset->zsl->length) {
+        dictAdd(c->db->dict,dstkey,dstobj);
+        incrRefCount(dstkey);
+        addReplyLong(c, dstzset->zsl->length);
+        server.dirty++;
+    } else {
+        decrRefCount(dstzset);
+        addReply(c, shared.czero);
+    }
     zfree(src);
 }
 
@@ -5962,8 +5986,12 @@ static void hdelCommand(redisClient *c) {
             (unsigned char*) field->ptr,
             sdslen(field->ptr), &deleted);
         decrRefCount(field);
+        if (zipmapLen((unsigned char*) o->ptr) == 0)
+            deleteKey(c->db,c->argv[1]);
     } else {
         deleted = dictDelete((dict*)o->ptr,c->argv[2]) == DICT_OK;
+        if (htNeedsResize(o->ptr)) dictResize(o->ptr);
+        if (dictSize((dict*)o->ptr) == 0) deleteKey(c->db,c->argv[1]);
     }
     if (deleted) server.dirty++;
     addReply(c,deleted ? shared.cone : shared.czero);
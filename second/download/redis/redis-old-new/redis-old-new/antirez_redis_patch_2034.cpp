@@ -19,6 +19,7 @@ void saddCommand(redisClient *c) {
     }
     if (dictAdd(set->ptr,c->argv[2],NULL) == DICT_OK) {
         incrRefCount(c->argv[2]);
+        touchWatchedKey(c->db,c->argv[1]);
         server.dirty++;
         addReply(c,shared.cone);
     } else {
@@ -34,6 +35,7 @@ void sremCommand(redisClient *c) {
 
     if (dictDelete(set->ptr,c->argv[2]) == DICT_OK) {
         server.dirty++;
+        touchWatchedKey(c->db,c->argv[1]);
         if (htNeedsResize(set->ptr)) dictResize(set->ptr);
         if (dictSize((dict*)set->ptr) == 0) dbDelete(c->db,c->argv[1]);
         addReply(c,shared.cone);
@@ -67,6 +69,8 @@ void smoveCommand(redisClient *c) {
     }
     if (dictSize((dict*)srcset->ptr) == 0 && srcset != dstset)
         dbDelete(c->db,c->argv[1]);
+    touchWatchedKey(c->db,c->argv[1]);
+    touchWatchedKey(c->db,c->argv[2]);
     server.dirty++;
     /* Add the element to the destination set */
     if (!dstset) {
@@ -118,6 +122,7 @@ void spopCommand(redisClient *c) {
         dictDelete(set->ptr,ele);
         if (htNeedsResize(set->ptr)) dictResize(set->ptr);
         if (dictSize((dict*)set->ptr) == 0) dbDelete(c->db,c->argv[1]);
+        touchWatchedKey(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -161,8 +166,10 @@ void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long setsnum
         if (!setobj) {
             zfree(dv);
             if (dstkey) {
-                if (dbDelete(c->db,dstkey))
+                if (dbDelete(c->db,dstkey)) {
+                    touchWatchedKey(c->db,dstkey);
                     server.dirty++;
+                }
                 addReply(c,shared.czero);
             } else {
                 addReply(c,shared.emptymultibulk);
@@ -229,6 +236,7 @@ void sinterGenericCommand(redisClient *c, robj **setskeys, unsigned long setsnum
             decrRefCount(dstset);
             addReply(c,shared.czero);
         }
+        touchWatchedKey(c->db,dstkey);
         server.dirty++;
     } else {
         lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
@@ -327,6 +335,7 @@ void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj
             decrRefCount(dstset);
             addReply(c,shared.czero);
         }
+        touchWatchedKey(c->db,dstkey);
         server.dirty++;
     }
     zfree(dv);
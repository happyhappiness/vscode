@@ -188,6 +188,7 @@ void saddCommand(redisClient *c) {
         }
     }
     if (setTypeAdd(set,c->argv[2])) {
+        touchWatchedKey(c->db,c->argv[1]);
         server.dirty++;
         addReply(c,shared.cone);
     } else {
@@ -203,6 +204,7 @@ void sremCommand(redisClient *c) {
 
     if (setTypeRemove(set,c->argv[2])) {
         if (setTypeSize(set) == 0) dbDelete(c->db,c->argv[1]);
+        touchWatchedKey(c->db,c->argv[1]);
         server.dirty++;
         addReply(c,shared.cone);
     } else {
@@ -241,6 +243,8 @@ void smoveCommand(redisClient *c) {
 
     /* Remove the src set from the database when empty */
     if (setTypeSize(srcset) == 0) dbDelete(c->db,c->argv[1]);
+    touchWatchedKey(c->db,c->argv[1]);
+    touchWatchedKey(c->db,c->argv[2]);
     server.dirty++;
 
     /* Create the destination set when it doesn't exist */
@@ -289,6 +293,7 @@ void spopCommand(redisClient *c) {
         addReplyBulk(c,ele);
         decrRefCount(ele);
         if (setTypeSize(set) == 0) dbDelete(c->db,c->argv[1]);
+        touchWatchedKey(c->db,c->argv[1]);
         server.dirty++;
     }
 }
@@ -325,8 +330,10 @@ void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum,
         if (!setobj) {
             zfree(sets);
             if (dstkey) {
-                if (dbDelete(c->db,dstkey))
+                if (dbDelete(c->db,dstkey)) {
+                    touchWatchedKey(c->db,dstkey);
                     server.dirty++;
+                }
                 addReply(c,shared.czero);
             } else {
                 addReply(c,shared.emptymultibulk);
@@ -390,6 +397,7 @@ void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum,
             decrRefCount(dstset);
             addReply(c,shared.czero);
         }
+        touchWatchedKey(c->db,dstkey);
         server.dirty++;
     } else {
         lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
@@ -481,6 +489,7 @@ void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *
             decrRefCount(dstset);
             addReply(c,shared.czero);
         }
+        touchWatchedKey(c->db,dstkey);
         server.dirty++;
     }
     zfree(sets);
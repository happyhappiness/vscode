     robj *zobj;
     int deleted = 0, keyremoved = 0, j;
 
     if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
         checkType(c,zobj,OBJ_ZSET)) return;
 
-    if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
-        unsigned char *eptr;
-
-        for (j = 2; j < c->argc; j++) {
-            if ((eptr = zzlFind(zobj->ptr,c->argv[j],NULL)) != NULL) {
-                deleted++;
-                zobj->ptr = zzlDelete(zobj->ptr,eptr);
-                if (zzlLength(zobj->ptr) == 0) {
-                    dbDelete(c->db,key);
-                    keyremoved = 1;
-                    break;
-                }
-            }
-        }
-    } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
-        zset *zs = zobj->ptr;
-        dictEntry *de;
-        double score;
-
-        for (j = 2; j < c->argc; j++) {
-            de = dictFind(zs->dict,c->argv[j]);
-            if (de != NULL) {
-                deleted++;
-
-                /* Delete from the skiplist */
-                score = *(double*)dictGetVal(de);
-                serverAssertWithInfo(c,c->argv[j],zslDelete(zs->zsl,score,c->argv[j]));
-
-                /* Delete from the hash table */
-                dictDelete(zs->dict,c->argv[j]);
-                if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-                if (dictSize(zs->dict) == 0) {
-                    dbDelete(c->db,key);
-                    keyremoved = 1;
-                    break;
-                }
-            }
+    for (j = 2; j < c->argc; j++) {
+        if (zsetDel(zobj,c->argv[j]->ptr)) deleted++;
+        if (zsetLength(zobj) == 0) {
+            dbDelete(c->db,key);
+            keyremoved = 1;
+            break;
         }
-    } else {
-        serverPanic("Unknown sorted set encoding");
     }
 
     if (deleted) {
         notifyKeyspaceEvent(NOTIFY_ZSET,"zrem",key,c->db->id);
         if (keyremoved)
             notifyKeyspaceEvent(NOTIFY_GENERIC,"del",key,c->db->id);

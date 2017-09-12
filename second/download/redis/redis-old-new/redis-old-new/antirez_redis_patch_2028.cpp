@@ -394,11 +394,7 @@ int removeExpire(redisDb *db, robj *key) {
     /* An expire may only be removed if there is a corresponding entry in the
      * main dict. Otherwise, the key will never be freed. */
     redisAssert(dictFind(db->dict,key->ptr) != NULL);
-    if (dictDelete(db->expires,key->ptr) == DICT_OK) {
-        return 1;
-    } else {
-        return 0;
-    }
+    return dictDelete(db->expires,key->ptr) == DICT_OK;
 }
 
 void setExpire(redisDb *db, robj *key, time_t when) {
@@ -528,3 +524,17 @@ void ttlCommand(redisClient *c) {
     }
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
 }
+
+void persistCommand(redisClient *c) {
+    dictEntry *de;
+
+    de = dictFind(c->db->dict,c->argv[1]->ptr);
+    if (de == NULL) {
+        addReply(c,shared.czero);
+    } else {
+        if (removeExpire(c->db,c->argv[1]))
+            addReply(c,shared.cone);
+        else
+            addReply(c,shared.czero);
+    }
+}
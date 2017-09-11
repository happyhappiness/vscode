@@ -296,6 +296,29 @@ void debugCommand(redisClient *c) {
             (void*)val, val->refcount,
             strenc, (long long) rdbSavedObjectLen(val),
             val->lru, estimateObjectIdleTime(val));
+    } else if (!strcasecmp(c->argv[1]->ptr,"sdslen") && c->argc == 3) {
+        dictEntry *de;
+        robj *val;
+        sds key;
+
+        if ((de = dictFind(c->db->dict,c->argv[2]->ptr)) == NULL) {
+            addReply(c,shared.nokeyerr);
+            return;
+        }
+        val = dictGetVal(de);
+        key = dictGetKey(de);
+
+        if (val->type != REDIS_STRING || !sdsEncodedObject(val)) {
+            addReplyError(c,"Not an sds encoded string.");
+        } else {
+            addReplyStatusFormat(c,
+                "key_sds_len:%lld, key_sds_avail:%lld, "
+                "val_sds_len:%lld, val_sds_avail:%lld",
+                (long long) sdslen(key),
+                (long long) sdsavail(key),
+                (long long) sdslen(val->ptr),
+                (long long) sdsavail(val->ptr));
+        }
     } else if (!strcasecmp(c->argv[1]->ptr,"populate") && c->argc == 3) {
         long keys, j;
         robj *key, *val;
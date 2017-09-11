@@ -409,12 +409,14 @@ void debugCommand(client *c) {
             addReplyError(c,"Not an sds encoded string.");
         } else {
             addReplyStatusFormat(c,
-                "key_sds_len:%lld, key_sds_avail:%lld, "
-                "val_sds_len:%lld, val_sds_avail:%lld",
+                "key_sds_len:%lld, key_sds_avail:%lld, key_zmalloc: %lld, "
+                "val_sds_len:%lld, val_sds_avail:%lld, val_zmalloc: %lld",
                 (long long) sdslen(key),
                 (long long) sdsavail(key),
+                (long long) sdsZmallocSize(key),
                 (long long) sdslen(val->ptr),
-                (long long) sdsavail(val->ptr));
+                (long long) sdsavail(val->ptr),
+                (long long) getStringObjectSdsUsedMemory(val));
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"populate") &&
                (c->argc == 3 || c->argc == 4)) {
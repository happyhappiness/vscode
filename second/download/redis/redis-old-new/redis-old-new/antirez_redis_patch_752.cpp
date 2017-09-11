@@ -325,7 +325,8 @@ void debugCommand(redisClient *c) {
                 (long long) sdslen(val->ptr),
                 (long long) sdsavail(val->ptr));
         }
-    } else if (!strcasecmp(c->argv[1]->ptr,"populate") && c->argc == 3) {
+    } else if (!strcasecmp(c->argv[1]->ptr,"populate") &&
+               (c->argc == 3 || c->argc == 4)) {
         long keys, j;
         robj *key, *val;
         char buf[128];
@@ -334,7 +335,8 @@ void debugCommand(redisClient *c) {
             return;
         dictExpand(c->db->dict,keys);
         for (j = 0; j < keys; j++) {
-            snprintf(buf,sizeof(buf),"key:%lu",j);
+            snprintf(buf,sizeof(buf),"%s:%lu",
+                (c->argc == 3) ? "key" : c->argv[3]->ptr, j);
             key = createStringObject(buf,strlen(buf));
             if (lookupKeyRead(c->db,key) != NULL) {
                 decrRefCount(key);
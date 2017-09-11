@@ -338,7 +338,7 @@ void debugCommand(redisClient *c) {
             snprintf(buf,sizeof(buf),"%s:%lu",
                 (c->argc == 3) ? "key" : (char*)c->argv[3]->ptr, j);
             key = createStringObject(buf,strlen(buf));
-            if (lookupKeyRead(c->db,key) != NULL) {
+            if (lookupKeyWrite(c->db,key) != NULL) {
                 decrRefCount(key);
                 continue;
             }
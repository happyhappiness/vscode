@@ -336,7 +336,7 @@ void debugCommand(redisClient *c) {
         dictExpand(c->db->dict,keys);
         for (j = 0; j < keys; j++) {
             snprintf(buf,sizeof(buf),"%s:%lu",
-                (c->argc == 3) ? "key" : c->argv[3]->ptr, j);
+                (c->argc == 3) ? "key" : (char*)c->argv[3]->ptr, j);
             key = createStringObject(buf,strlen(buf));
             if (lookupKeyRead(c->db,key) != NULL) {
                 decrRefCount(key);
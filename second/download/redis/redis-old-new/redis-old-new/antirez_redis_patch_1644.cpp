@@ -425,7 +425,7 @@ int rdbSave(char *filename) {
             strerror(errno));
         return REDIS_ERR;
     }
-    if (fwrite("REDIS0001",9,1,fp) == 0) goto werr;
+    if (fwrite("REDIS0002",9,1,fp) == 0) goto werr;
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;
         dict *d = db->dict;
@@ -931,7 +931,7 @@ int rdbLoad(char *filename) {
         return REDIS_ERR;
     }
     rdbver = atoi(buf+5);
-    if (rdbver != 1) {
+    if (rdbver < 1 || rdbver > 2) {
         fclose(fp);
         redisLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
         return REDIS_ERR;
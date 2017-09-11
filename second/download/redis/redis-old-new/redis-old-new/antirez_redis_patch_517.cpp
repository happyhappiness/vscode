@@ -869,9 +869,9 @@ int rdbSave(char *filename) {
     return REDIS_OK;
 
 werr:
+    redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
-    redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
     return REDIS_ERR;
 }
 
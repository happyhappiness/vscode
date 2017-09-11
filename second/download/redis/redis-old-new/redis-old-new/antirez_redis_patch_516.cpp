@@ -1146,9 +1146,9 @@ int rewriteAppendOnlyFile(char *filename) {
     return REDIS_OK;
 
 werr:
+    redisLog(REDIS_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
-    redisLog(REDIS_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
     if (di) dictReleaseIterator(di);
     return REDIS_ERR;
 }
@@ -2329,7 +2329,7 @@ static int rdbSave(char *filename) {
     /* Use RENAME to make sure the DB file is changed atomically only
      * if the generate DB file is ok. */
     if (rename(tmpfile,filename) == -1) {
-        redisLog(REDIS_WARNING,"Error moving temp DB file on the final destionation: %s", strerror(errno));
+        redisLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
         unlink(tmpfile);
         return REDIS_ERR;
     }
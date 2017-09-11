@@ -688,7 +688,7 @@ int rdbSave(char *filename) {
      * loading code skips the check in this case. */
     cksum = rdb.cksum;
     memrev64ifbe(&cksum);
-    rioWrite(&rdb,&cksum,8);
+    if (rioWrite(&rdb,&cksum,8) == 0) goto werr;
 
     /* Make sure data will not remain on the OS's output buffers */
     if (fflush(fp) == EOF) goto werr;
@@ -766,7 +766,7 @@ int rdbSaveBackground(char *filename) {
 void rdbRemoveTempFile(pid_t childpid) {
     char tmpfile[256];
 
-    snprintf(tmpfile,256,"temp-%d.rdb", (int) childpid);
+    snprintf(tmpfile,sizeof(tmpfile),"temp-%d.rdb", (int) childpid);
     unlink(tmpfile);
 }
 
@@ -943,7 +943,7 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
 
             /* Add pair to hash table */
             ret = dictAdd((dict*)o->ptr, field, value);
-            redisAssert(ret == REDIS_OK);
+            redisAssert(ret == DICT_OK);
         }
 
         /* All pairs should be read by now */
@@ -190,7 +190,7 @@ int dsSet(redisDb *db, robj *key, robj *val) {
 
     len = dsKeyToPath(db,buf,key);
     memcpy(buf2,buf,len);
-    snprintf(buf2+len,sizeof(buf2)-len,"_%ld_%ld",(long)time(NULL),(long)val);
+    snprintf(buf2+len,sizeof(buf2)-len,"-%ld-%ld",(long)time(NULL),(long)val);
     while ((fp = fopen(buf2,"w")) == NULL) {
         if (errno == ENOSPC) {
             redisLog(REDIS_WARNING,"Diskstore: No space left on device. Please make room and wait 30 seconds for Redis to continue.");
@@ -401,6 +401,8 @@ void *dsRdbSave_thread(void *arg) {
                 readdir_r(dir,&de,&dp);
                 if (dp == NULL) break;
                 if (dp->d_name[0] == '.') continue;
+                /* If there is a '-' char in the file name, it's a temp file */
+                if (strchr(dp->d_name,'-') != NULL) continue;
 
                 /* Emit the SELECT DB opcode if needed. */
                 dbid = dsGetDbidFromFilename(dp->d_name);
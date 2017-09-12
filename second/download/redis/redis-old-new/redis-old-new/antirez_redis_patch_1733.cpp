@@ -295,6 +295,17 @@ int dsExists(redisDb *db, robj *key) {
     return access(buf,R_OK) == 0;
 }
 
+int dsGetDbidFromFilename(char *path) {
+    char id[64];
+    char *p = strchr(path,'_');
+    int len = (p - path);
+
+    redisAssert(p != NULL && len < 64);
+    memcpy(id,path,len);
+    id[len] = '\0';
+    return atoi(id);
+}
+
 void dsFlushOneDir(char *path, int dbid) {
     DIR *dir;
     struct dirent *dp, de;
@@ -313,17 +324,8 @@ void dsFlushOneDir(char *path, int dbid) {
         if (dp->d_name[0] == '.') continue;
 
         /* Check if we need to remove this entry accordingly to the
-         * DB number */
-        if (dbid != -1) {
-            char id[64];
-            char *p = strchr(dp->d_name,'_');
-            int len = (p - dp->d_name);
-
-            redisAssert(p != NULL && len < 64);
-            memcpy(id,dp->d_name,len);
-            id[len] = '\0';
-            if (atoi(id) != dbid) continue; /* skip this file */
-        }
+         * DB number. */
+        if (dbid != -1 && dsGetDbidFromFilename(dp->d_name)) continue;
         
         /* Finally unlink the file */
         snprintf(buf,1024,"%s/%s",path,dp->d_name);
@@ -357,14 +359,13 @@ void dsRdbSaveSetState(int state) {
 
 void *dsRdbSave_thread(void *arg) {
     char tmpfile[256], *filename = (char*)arg;
-    int j, i;
-    time_t now = time(NULL);
+    struct dirent *dp, de;
+    int j, i, last_dbid = -1;
     FILE *fp;
 
     /* Change state to ACTIVE, to signal there is a saving thead working. */
-    pthread_mutex_lock(&server.bgsavethread_mutex);
-    server.bgsavethread_state = REDIS_BGSAVE_THREAD_ACTIVE;
-    pthread_mutex_unlock(&server.bgsavethread_mutex);
+    redisLog(REDIS_NOTICE,"Diskstore BGSAVE thread started");
+    dsRdbSaveSetState(REDIS_BGSAVE_THREAD_ACTIVE);
 
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
@@ -378,18 +379,71 @@ void *dsRdbSave_thread(void *arg) {
 
     sleep(5);
 
-#if 0
     /* Scan all diskstore dirs looking for keys */
     for (j = 0; j < 256; j++) {
         for (i = 0; i < 256; i++) {
-            snprintf(buf,1024,"%s/%02x/%02x",server.ds_path,j,i);
-
-            /* Write the SELECT DB opcode */
-            if (rdbSaveType(fp,REDIS_SELECTDB) == -1) goto werr;
-            if (rdbSaveLen(fp,j) == -1) goto werr;
+            DIR *dir;
+            char buf[1024];
+
+            /* For every directory, collect all the keys */
+            snprintf(buf,sizeof(buf),"%s/%02x/%02x",server.ds_path,j,i);
+            if ((dir = opendir(buf)) == NULL) {
+                redisLog(REDIS_WARNING,"Disk store can't open dir %s: %s",
+                    buf, strerror(errno));
+                goto werr;
+            }
+
+            while(1) {
+                char buf[1024];
+                int dbid;
+                FILE *entryfp;
+
+                readdir_r(dir,&de,&dp);
+                if (dp == NULL) break;
+                if (dp->d_name[0] == '.') continue;
+
+                /* Emit the SELECT DB opcode if needed. */
+                dbid = dsGetDbidFromFilename(dp->d_name);
+                if (dbid != last_dbid) {
+                    last_dbid = dbid;
+                    if (rdbSaveType(fp,REDIS_SELECTDB) == -1) goto werr;
+                    if (rdbSaveLen(fp,dbid) == -1) goto werr;
+                }
+
+                /* Let's copy this file into the target .rdb */
+                snprintf(buf,sizeof(buf),"%s/%02x/%02x/%s",
+                    server.ds_path,j,i,dp->d_name);
+                if ((entryfp = fopen(buf,"r")) == NULL) {
+                    redisLog(REDIS_WARNING,"Can't open %s: %s",
+                        buf,strerror(errno));
+                    closedir(dir);
+                    goto werr;
+                }
+                while(1) {
+                    int nread = fread(buf,1,sizeof(buf),entryfp);
+
+                    if (nread == 0) {
+                        if (ferror(entryfp)) {
+                            redisLog(REDIS_WARNING,"Error reading from file entry while performing BGSAVE for diskstore: %s", strerror(errno));
+                            closedir(dir);
+                            goto werr;
+                        } else {
+                            break;
+                        }
+                    }
+                    if (fwrite(buf,1,nread,fp) != (unsigned)nread) {
+                        closedir(dir);
+                        goto werr;
+                    }
+                }
+                fclose(entryfp);
+            }
+            closedir(dir);
         }
     }
-#endif
+    
+    /* Output the end of file opcode */
+    if (rdbSaveType(fp,REDIS_EOF) == -1) goto werr;
 
     /* Make sure data will not remain on the OS's output buffers */
     fflush(fp);
@@ -405,7 +459,7 @@ void *dsRdbSave_thread(void *arg) {
         dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_ERR);
         return NULL;
     }
-    redisLog(REDIS_NOTICE,"DB saved on disk");
+    redisLog(REDIS_NOTICE,"DB saved on disk by diskstore thread");
     dsRdbSaveSetState(REDIS_BGSAVE_THREAD_DONE_OK);
     return NULL;
 
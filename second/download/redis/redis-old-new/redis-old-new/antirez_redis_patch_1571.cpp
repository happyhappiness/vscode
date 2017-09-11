@@ -8,6 +8,8 @@
 #include <sys/resource.h>
 #include <sys/wait.h>
 
+void aofUpdateCurrentSize(void);
+
 /* Called when the user switches from "appendonly yes" to "appendonly no"
  * at runtime using the CONFIG command. */
 void stopAppendOnly(void) {
@@ -19,15 +21,15 @@ void stopAppendOnly(void) {
     server.appendseldb = -1;
     server.appendonly = 0;
     /* rewrite operation in progress? kill it, wait child exit */
-    if (server.bgsavechildpid != -1) {
+    if (server.bgrewritechildpid != -1) {
         int statloc;
 
-        if (kill(server.bgsavechildpid,SIGKILL) != -1)
+        if (kill(server.bgrewritechildpid,SIGKILL) != -1)
             wait3(&statloc,0,NULL);
         /* reset the buffer accumulating changes while the child saves */
         sdsfree(server.bgrewritebuf);
         server.bgrewritebuf = sdsempty();
-        server.bgsavechildpid = -1;
+        server.bgrewritechildpid = -1;
     }
 }
 
@@ -82,6 +84,7 @@ void flushAppendOnlyFile(void) {
     }
     sdsfree(server.aofbuf);
     server.aofbuf = sdsempty();
+    server.appendonly_current_size += nwritten;
 
     /* Don't Fsync if no-appendfsync-on-rewrite is set to yes and we have
      * childs performing heavy I/O on disk. */
@@ -221,6 +224,7 @@ int loadAppendOnlyFile(char *filename) {
     long loops = 0;
 
     if (fp && redis_fstat(fileno(fp),&sb) != -1 && sb.st_size == 0) {
+        server.appendonly_current_size = 0;
         fclose(fp);
         return REDIS_ERR;
     }
@@ -299,6 +303,8 @@ int loadAppendOnlyFile(char *filename) {
     freeFakeClient(fakeClient);
     server.appendonly = appendonly;
     stopLoading();
+    aofUpdateCurrentSize();
+    server.auto_aofrewrite_base_size = server.appendonly_current_size;
     return REDIS_OK;
 
 readerr:
@@ -565,16 +571,18 @@ int rewriteAppendOnlyFile(char *filename) {
  */
 int rewriteAppendOnlyFileBackground(void) {
     pid_t childpid;
+    long long start;
 
     if (server.bgrewritechildpid != -1) return REDIS_ERR;
     if (server.ds_enabled != 0) {
         redisLog(REDIS_WARNING,"BGREWRITEAOF called with diskstore enabled: AOF is not supported when diskstore is enabled. Operation not performed.");
         return REDIS_ERR;
     }
+    start = ustime();
     if ((childpid = fork()) == 0) {
-        /* Child */
         char tmpfile[256];
 
+        /* Child */
         if (server.ipfd > 0) close(server.ipfd);
         if (server.sofd > 0) close(server.sofd);
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
@@ -585,6 +593,7 @@ int rewriteAppendOnlyFileBackground(void) {
         }
     } else {
         /* Parent */
+        server.stat_fork_time = ustime()-start;
         if (childpid == -1) {
             redisLog(REDIS_WARNING,
                 "Can't rewrite append only file in background: fork: %s",
@@ -608,9 +617,10 @@ int rewriteAppendOnlyFileBackground(void) {
 void bgrewriteaofCommand(redisClient *c) {
     if (server.bgrewritechildpid != -1) {
         addReplyError(c,"Background append only file rewriting already in progress");
-        return;
-    }
-    if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
+    } else if (server.bgsavechildpid != -1) {
+        server.aofrewrite_scheduled = 1;
+        addReplyStatus(c,"Background append only file rewriting scheduled");
+    } else if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
         addReplyStatus(c,"Background append only file rewriting started");
     } else {
         addReply(c,shared.err);
@@ -624,6 +634,21 @@ void aofRemoveTempFile(pid_t childpid) {
     unlink(tmpfile);
 }
 
+/* Update the server.appendonly_current_size filed explicitly using stat(2)
+ * to check the size of the file. This is useful after a rewrite or after
+ * a restart, normally the size is updated just adding the write length
+ * to the current lenght, that is much faster. */
+void aofUpdateCurrentSize(void) {
+    struct redis_stat sb;
+
+    if (redis_fstat(server.appendfd,&sb) == -1) {
+        redisLog(REDIS_WARNING,"Unable to check the AOF length: %s",
+            strerror(errno));
+    } else {
+        server.appendonly_current_size = sb.st_size;
+    }
+}
+
 /* A background append only file rewriting (BGREWRITEAOF) terminated its work.
  * Handle this. */
 void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
@@ -664,6 +689,8 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             if (server.appendfsync != APPENDFSYNC_NO) aof_fsync(fd);
             server.appendseldb = -1; /* Make sure it will issue SELECT */
             redisLog(REDIS_NOTICE,"The new append only file was selected for future appends.");
+            aofUpdateCurrentSize();
+            server.auto_aofrewrite_base_size = server.appendonly_current_size;
         } else {
             /* If append only is disabled we just generate a dump in this
              * format. Why not? */
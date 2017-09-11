@@ -1,4 +1,5 @@
 #include "redis.h"
+#include "bio.h"
 
 #include <signal.h>
 #include <fcntl.h>
@@ -677,8 +678,10 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         redisLog(REDIS_NOTICE,
             "Background AOF rewrite terminated with success");
 
-        /* Flush the differences accumulated by the parent to the rewritten AOF. */
-        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int)server.bgrewritechildpid);
+        /* Flush the differences accumulated by the parent to the
+         * rewritten AOF. */
+        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof",
+            (int)server.bgrewritechildpid);
         newfd = open(tmpfile,O_WRONLY|O_APPEND);
         if (newfd == -1) {
             redisLog(REDIS_WARNING,
@@ -704,7 +707,10 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
 
         /* The only remaining thing to do is to rename the temporary file to
          * the configured file and switch the file descriptor used to do AOF
-         * writes. There are two possible scenarios:
+         * writes. We don't want close(2) or rename(2) calls to block the
+         * server on old file deletion.
+         *
+         * There are two possible scenarios:
          *
          * 1) AOF is DISABLED and this was a one time rewrite. The temporary
          * file will be renamed to the configured file. When this file already
@@ -719,7 +725,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
          *
          * To mitigate the blocking effect of the unlink operation (either
          * caused by rename(2) in scenario 1, or by close(2) in scenario 2), we
-         * use a background thread in libeio to take care of this. First, we
+         * use a background thread to take care of this. First, we
          * make scenario 1 identical to scenario 2 by opening the target file
          * when it exists. The unlink operation after the rename(2) will then
          * be executed upon calling close(2) for its descriptor. Everything to
@@ -728,19 +734,14 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
          * is, as long as the file descriptor is released again. */
         if (server.appendfd == -1) {
             /* AOF disabled */
-            struct stat st;
 
-            /* Check if the configured filename exists. If so, we need to open
-             * it to prevent rename(2) from unlinking it. */
-            if (stat(server.appendfilename, &st) == ENOENT) {
-                oldfd = -1;
-            } else {
-                /* Don't care if this fails: oldfd will be -1. */
-                oldfd = open(server.appendfilename,O_RDONLY|O_NONBLOCK);
-            }
+             /* Don't care if this fails: oldfd will be -1 and we handle that.
+              * One notable case of -1 return is if the old file does
+              * not exist. */
+             oldfd = open(server.appendfilename,O_RDONLY|O_NONBLOCK);
         } else {
             /* AOF enabled */
-            oldfd = -1;
+            oldfd = -1; /* We'll set this to the current AOF filedes later. */
         }
 
         /* Rename the temporary file. This will not unlink the target file if
@@ -749,16 +750,16 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             redisLog(REDIS_WARNING,
                 "Error trying to rename the temporary AOF: %s", strerror(errno));
             close(newfd);
-            if (oldfd != -1)
-                close(oldfd);
+            if (oldfd != -1) close(oldfd);
             goto cleanup;
         }
 
         if (server.appendfd == -1) {
-            /* AOF disabled */
+            /* AOF disabled, we don't need to set the AOF file descriptor
+             * to this new file, so we can close it. */
             close(newfd);
         } else {
-            /* AOF enabled */
+            /* AOF enabled, replace the old fd with the new one. */
             oldfd = server.appendfd;
             server.appendfd = newfd;
             if (server.appendfsync != APPENDFSYNC_NO) aof_fsync(newfd);
@@ -770,7 +771,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         redisLog(REDIS_NOTICE, "Background AOF rewrite successful");
 
         /* Asynchronously close the overwritten AOF. */
-        if (oldfd != -1) eio_close(oldfd, 0, NULL, 0);
+        if (oldfd != -1) bioCreateBackgroundJob(REDIS_BIO_CLOSE_FILE,(void*)(long)oldfd);
 
         redisLog(REDIS_VERBOSE,
             "Background AOF rewrite signal handler took %lldus", ustime()-now);
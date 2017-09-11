@@ -39,6 +39,7 @@
 #include <sys/wait.h>
 #include <arpa/inet.h>
 #include <sys/stat.h>
+#include <sys/param.h>
 
 #define RDB_LOAD_NONE   0
 #define RDB_LOAD_ENC    (1<<0)
@@ -844,14 +845,20 @@ int rdbSaveRioWithEOFMark(rio *rdb, int *error) {
 /* Save the DB on disk. Return C_ERR on error, C_OK on success. */
 int rdbSave(char *filename) {
     char tmpfile[256];
+    char cwd[MAXPATHLEN]; /* Current working dir path for error messages. */
     FILE *fp;
     rio rdb;
     int error = 0;
 
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
-        serverLog(LL_WARNING, "Failed opening .rdb for saving: %s",
+        char *cwdp = getcwd(cwd,MAXPATHLEN);
+        serverLog(LL_WARNING,
+            "Failed opening the RDB file %s (in server root dir %s) "
+            "for saving: %s",
+            filename,
+            cwdp ? cwdp : "unknown",
             strerror(errno));
         return C_ERR;
     }
@@ -870,10 +877,18 @@ int rdbSave(char *filename) {
     /* Use RENAME to make sure the DB file is changed atomically only
      * if the generate DB file is ok. */
     if (rename(tmpfile,filename) == -1) {
-        serverLog(LL_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
+        char *cwdp = getcwd(cwd,MAXPATHLEN);
+        serverLog(LL_WARNING,
+            "Error moving temp DB file %s on the final "
+            "destination %s (in server root dir %s): %s",
+            tmpfile,
+            filename,
+            cwdp ? cwdp : "unknown",
+            strerror(errno));
         unlink(tmpfile);
         return C_ERR;
     }
+
     serverLog(LL_NOTICE,"DB saved on disk");
     server.dirty = 0;
     server.lastsave = time(NULL);
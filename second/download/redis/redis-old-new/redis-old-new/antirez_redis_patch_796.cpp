@@ -766,7 +766,7 @@ int rdbSaveBackground(char *filename) {
 void rdbRemoveTempFile(pid_t childpid) {
     char tmpfile[256];
 
-    snprintf(tmpfile,256,"temp-%d.rdb", (int) childpid);
+    snprintf(tmpfile,sizeof(tmpfile),"temp-%d.rdb", (int) childpid);
     unlink(tmpfile);
 }
 
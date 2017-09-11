@@ -720,7 +720,7 @@ int rdbSave(char *filename) {
     char tmpfile[256];
     FILE *fp;
     rio rdb;
-    int error;
+    int error = 0;
 
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
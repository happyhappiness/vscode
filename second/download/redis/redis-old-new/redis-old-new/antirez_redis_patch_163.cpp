@@ -111,6 +111,7 @@
 #include <string.h>
 #include <stdlib.h>
 #include <ctype.h>
+#include <sys/stat.h>
 #include <sys/types.h>
 #include <sys/ioctl.h>
 #include <unistd.h>
@@ -1160,10 +1161,14 @@ int linenoiseHistorySetMaxLen(int len) {
 /* Save the history in the specified file. On success 0 is returned
  * otherwise -1 is returned. */
 int linenoiseHistorySave(const char *filename) {
-    FILE *fp = fopen(filename,"w");
+    mode_t old_umask = umask(S_IXUSR|S_IRWXG|S_IRWXO);
+    FILE *fp;
     int j;
 
+    fp = fopen(filename,"w");
+    umask(old_umask);
     if (fp == NULL) return -1;
+    chmod(filename,S_IRUSR|S_IWUSR);
     for (j = 0; j < history_len; j++)
         fprintf(fp,"%s\n",history[j]);
     fclose(fp);
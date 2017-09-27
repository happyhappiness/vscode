 #define ERRMSGSZ        128
 
 #ifndef MAX_PATH
 #define MAX_PATH        1024
 #endif
 
+static void usage(const char *argv0, const char *reason)
+{
+    if (reason) {
+        fprintf(stderr, "%s\n", reason);
+    }
+    fprintf(stderr,
+            "Usage: %s [-l] <logfile> "
+            "{<rotation time in seconds>|<rotation size in megabytes>} "
+            "[offset minutes from UTC]\n\n",
+            argv0);
+#ifdef OS2
+    fprintf(stderr,
+            "Add this:\n\nTransferLog \"|%s.exe /some/where 86400\"\n\n",
+            argv0);
+#else
+    fprintf(stderr,
+            "Add this:\n\nTransferLog \"|%s /some/where 86400\"\n\n",
+            argv0);
+    fprintf(stderr,
+            "or \n\nTransferLog \"|%s /some/where 5M\"\n\n", argv0);
+#endif
+    fprintf(stderr,
+            "to httpd.conf. The generated name will be /some/where.nnnn "
+            "where nnnn is the\nsystem time at which the log nominally "
+            "starts (N.B. if using a rotation time,\nthe time will always "
+            "be a multiple of the rotation time, so you can synchronize\n"
+            "cron scripts with it). At the end of each rotation time or "
+            "when the file size\nis reached a new log is started.\n");
+    exit(1);
+}
+
 int main (int argc, const char * const argv[])
 {
     char buf[BUFSIZE], buf2[MAX_PATH], errbuf[ERRMSGSZ];
     int tLogEnd = 0, tRotation = 0, utc_offset = 0;
     unsigned int sRotation = 0;
     int nMessCount = 0;

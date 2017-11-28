 
 static void
 mail_warranty(void)
 {
     FILE *fp = NULL;
     static char command[256];
-#if HAVE_MKSTEMP
 
+    const mode_t prev_umask=umask(S_IRWXU);
+
+#if HAVE_MKSTEMP
     char filename[] = "/tmp/squid-XXXXXX";
     int tfd = mkstemp(filename);
-
-    if (tfd < 0)
+    if (tfd < 0 || (fp = fdopen(tfd, "w")) == NULL) {
+        umask(prev_umask);
         return;
-
-    if ((fp = fdopen(tfd, "w")) == NULL)
-        return;
-
+    }
 #else
-
     char *filename;
-
-    if ((filename = tempnam(NULL, APP_SHORTNAME)) == NULL)
+    // XXX tempnam is obsolete since POSIX.2008-1
+    // tmpfile is not an option, we want the created files to stick around
+    if ((filename = tempnam(NULL, APP_SHORTNAME)) == NULL ||
+            (fp = fopen(filename, "w")) == NULL) {
+        umask(prev_umask);
         return;
-
-    if ((fp = fopen(filename, "w")) == NULL)
-        return;
-
+    }
 #endif
+    umask(prev_umask);
 
     if (Config.EmailFrom)
         fprintf(fp, "From: %s\n", Config.EmailFrom);
     else
         fprintf(fp, "From: %s@%s\n", APP_SHORTNAME, uniqueHostname());
 

 
 #endif
 
     debugs(0, DBG_IMPORTANT, "Rotate log file " << lf->path);
 
     /* Rotate numbers 0 through N up one */
-    for (i = Config.Log.rotateNumber; i > 1;) {
+    for (int16_t i = nRotate; i > 1;) {
         --i;
         snprintf(from, MAXPATHLEN, "%s.%d", realpath, i - 1);
         snprintf(to, MAXPATHLEN, "%s.%d", realpath, i);
         xrename(from, to);
     }
 
     /* Rotate the current log to .0 */
     logfileFlush(lf);
 
     file_close(ll->fd);     /* always close */
 
-    if (Config.Log.rotateNumber > 0) {
+    if (nRotate > 0) {
         snprintf(to, MAXPATHLEN, "%s.%d", realpath, 0);
         xrename(realpath, to);
     }
     /* Reopen the log.  It may have been renamed "manually" */
     ll->fd = file_open(realpath, O_WRONLY | O_CREAT | O_TEXT);
 
     if (DISK_ERROR == ll->fd && lf->flags.fatal) {
-        debugs(50, DBG_CRITICAL, "ERROR: logfileRotate: " << lf->path << ": " << xstrerror());
-        fatalf("Cannot open %s: %s", lf->path, xstrerror());
+        int xerrno = errno;
+        debugs(50, DBG_CRITICAL, MYNAME << "ERROR: " << lf->path << ": " << xstrerr(xerrno));
+        fatalf("Cannot open %s: %s", lf->path, xstrerr(xerrno));
     }
 }
 
 static void
 logfile_mod_stdio_close(Logfile * lf)
 {

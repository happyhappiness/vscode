 
 APR_DECLARE(apr_status_t) apr_file_puts(const char *str, apr_file_t *thefile)
 {
     return apr_file_write_full(thefile, str, strlen(str), NULL);
 }
 
-APR_DECLARE(apr_status_t) apr_file_flush(apr_file_t *thefile)
+apr_status_t apr_file_flush_locked(apr_file_t *thefile)
 {
-    if (thefile->buffered) {
-        apr_int64_t written = 0;
+    apr_status_t rv = APR_SUCCESS;
 
-        if (thefile->direction == 1 && thefile->bufpos) {
-            do {
-                written = write(thefile->filedes, thefile->buffer, thefile->bufpos);
-            } while (written == (apr_int64_t)-1 && errno == EINTR);
-            if (written == (apr_int64_t)-1) {
-                return errno;
-            }
+    if (thefile->direction == 1 && thefile->bufpos) {
+        apr_ssize_t written;
+
+        do {
+            written = write(thefile->filedes, thefile->buffer, thefile->bufpos);
+        } while (written == -1 && errno == EINTR);
+        if (written == -1) {
+            rv = errno;
+        } else {
             thefile->filePtr += written;
             thefile->bufpos = 0;
         }
     }
+
+    return rv;
+}
+
+APR_DECLARE(apr_status_t) apr_file_flush(apr_file_t *thefile)
+{
+    apr_status_t rv = APR_SUCCESS;
+
+    if (thefile->buffered) {
+        file_lock(thefile);
+        rv = apr_file_flush_locked(thefile);
+        file_unlock(thefile);
+    }
     /* There isn't anything to do if we aren't buffering the output
      * so just return success.
      */
-    return APR_SUCCESS; 
+    return rv; 
 }
 
 APR_DECLARE(apr_status_t) apr_file_gets(char *str, int len, apr_file_t *thefile)
 {
     apr_status_t rv = APR_SUCCESS; /* get rid of gcc warning */
     apr_size_t nbytes;

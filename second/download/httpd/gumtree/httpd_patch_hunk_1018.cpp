 
     return apr_file_read(thefile, ch, &nbytes);
 }
 
 APR_DECLARE(apr_status_t) apr_file_puts(const char *str, apr_file_t *thefile)
 {
-    apr_size_t nbytes = strlen(str);
-
-    return apr_file_write(thefile, str, &nbytes);
+    return apr_file_write_full(thefile, str, strlen(str), NULL);
 }
 
-apr_status_t apr_file_flush_locked(apr_file_t *thefile)
+APR_DECLARE(apr_status_t) apr_file_flush(apr_file_t *thefile)
 {
-    apr_status_t rv = APR_SUCCESS;
-
-    if (thefile->direction == 1 && thefile->bufpos) {
-        apr_ssize_t written;
+    if (thefile->buffered) {
+        apr_int64_t written = 0;
 
-        do {
-            written = write(thefile->filedes, thefile->buffer, thefile->bufpos);
-        } while (written == -1 && errno == EINTR);
-        if (written == -1) {
-            rv = errno;
-        } else {
+        if (thefile->direction == 1 && thefile->bufpos) {
+            do {
+                written = write(thefile->filedes, thefile->buffer, thefile->bufpos);
+            } while (written == (apr_int64_t)-1 && errno == EINTR);
+            if (written == (apr_int64_t)-1) {
+                return errno;
+            }
             thefile->filePtr += written;
             thefile->bufpos = 0;
         }
     }
-
-    return rv;
-}
-
-APR_DECLARE(apr_status_t) apr_file_flush(apr_file_t *thefile)
-{
-    apr_status_t rv = APR_SUCCESS;
-
-    if (thefile->buffered) {
-        file_lock(thefile);
-        rv = apr_file_flush_locked(thefile);
-        file_unlock(thefile);
-    }
     /* There isn't anything to do if we aren't buffering the output
      * so just return success.
      */
-    return rv; 
+    return APR_SUCCESS; 
 }
 
 APR_DECLARE(apr_status_t) apr_file_gets(char *str, int len, apr_file_t *thefile)
 {
     apr_status_t rv = APR_SUCCESS; /* get rid of gcc warning */
     apr_size_t nbytes;

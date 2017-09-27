     apr_file_close(f);
     return ret;
 }
 
 /* Soak up stderr from a script and redirect it to the error log. 
  */
-static void log_script_err(request_rec *r, apr_file_t *script_err)
+static apr_status_t log_script_err(request_rec *r, apr_file_t *script_err)
 {
     char argsbuffer[HUGE_STRING_LEN];
     char *newline;
+    apr_status_t rv;
 
-    while (apr_file_gets(argsbuffer, HUGE_STRING_LEN,
-                         script_err) == APR_SUCCESS) {
+    while ((rv = apr_file_gets(argsbuffer, HUGE_STRING_LEN,
+                               script_err)) == APR_SUCCESS) {
         newline = strchr(argsbuffer, '\n');
         if (newline) {
             *newline = '\0';
         }
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, 
                       "%s", argsbuffer);            
     }
+
+    return rv;
 }
 
 static int log_script(request_rec *r, cgi_server_conf * conf, int ret,
                       char *dbuf, const char *sbuf, apr_bucket_brigade *bb, 
                       apr_file_t *script_err)
 {

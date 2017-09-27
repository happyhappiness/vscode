     while ((rv = apr_file_gets(argsbuffer, HUGE_STRING_LEN,
                                script_err)) == APR_SUCCESS) {
         newline = strchr(argsbuffer, '\n');
         if (newline) {
             *newline = '\0';
         }
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, 
-                      "%s", argsbuffer);            
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                      "%s", argsbuffer);
     }
 
     return rv;
 }
 
 static int log_script(request_rec *r, cgi_server_conf * conf, int ret,
-                      char *dbuf, const char *sbuf, apr_bucket_brigade *bb, 
+                      char *dbuf, const char *sbuf, apr_bucket_brigade *bb,
                       apr_file_t *script_err)
 {
     const apr_array_header_t *hdrs_arr = apr_table_elts(r->headers_in);
     const apr_table_entry_t *hdrs = (const apr_table_entry_t *) hdrs_arr->elts;
     char argsbuffer[HUGE_STRING_LEN];
     apr_file_t *f = NULL;

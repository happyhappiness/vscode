 #include "mod_core.h"
 
 #define ASIS_MAGIC_TYPE "httpd/send-as-is"
 
 static int asis_handler(request_rec *r)
 {
-    conn_rec *c = r->connection;
-    apr_file_t *f = NULL;
+    apr_file_t *f;
     apr_status_t rv;
     const char *location;
 
-    if(strcmp(r->handler,ASIS_MAGIC_TYPE) && strcmp(r->handler,"send-as-is"))
+    if (strcmp(r->handler, ASIS_MAGIC_TYPE) && strcmp(r->handler, "send-as-is")) {
         return DECLINED;
+    }
 
     r->allowed |= (AP_METHOD_BIT << M_GET);
-    if (r->method_number != M_GET)
+    if (r->method_number != M_GET) {
         return DECLINED;
+    }
+
     if (r->finfo.filetype == APR_NOFILE) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01233)
                     "File does not exist: %s", r->filename);
         return HTTP_NOT_FOUND;
     }
 
     if ((rv = apr_file_open(&f, r->filename, APR_READ,
                 APR_OS_DEFAULT, r->pool)) != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01234)
                     "file permissions deny server access: %s", r->filename);
         return HTTP_FORBIDDEN;
     }
 
-    ap_scan_script_header_err(r, f, NULL);
+    ap_scan_script_header_err_ex(r, f, NULL, APLOG_MODULE_INDEX);
     location = apr_table_get(r->headers_out, "Location");
 
     if (location && location[0] == '/' &&
         ((r->status == HTTP_OK) || ap_is_HTTP_REDIRECT(r->status))) {
 
         apr_file_close(f);

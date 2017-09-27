     r->handler = old_handler;
 
     if (result == DECLINED && r->handler && r->filename) {
         ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
             "handler \"%s\" not found for: %s", r->handler, r->filename);
     }
+    if ((result != OK) && (result != DONE) && (result != DECLINED)
+        && !ap_is_HTTP_VALID_RESPONSE(result)) {
+        /* If a module is deliberately returning something else
+         * (request_rec in non-HTTP or proprietary extension?)
+         * let it set a note to allow it explicitly.
+         * Otherwise, a return code that is neither reserved nor HTTP
+         * is a bug, as in PR#31759.
+         */
+        ignore = apr_table_get(r->notes, "HTTP_IGNORE_RANGE");
+        if (!ignore) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                          "Handler for %s returned invalid result code %d",
+                          r->handler, result);
+            result = HTTP_INTERNAL_SERVER_ERROR;
+        }
+    }
 
     return result == DECLINED ? HTTP_INTERNAL_SERVER_ERROR : result;
 }
 
 AP_DECLARE(int) ap_method_is_limited(cmd_parms *cmd, const char *method)
 {

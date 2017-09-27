     r->handler = old_handler;
 
     if (result == DECLINED && r->handler && r->filename) {
         ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
             "handler \"%s\" not found for: %s", r->handler, r->filename);
     }
-    if ((result != OK) && (result != DONE) && (result != DECLINED)
-        && (result != AP_FILTER_ERROR)
+    if ((result != OK) && (result != DONE) && (result != DECLINED) && (result != SUSPENDED)
+        && (result != AP_FILTER_ERROR) /* ap_die() knows about this specifically */
         && !ap_is_HTTP_VALID_RESPONSE(result)) {
         /* If a module is deliberately returning something else
          * (request_rec in non-HTTP or proprietary extension?)
          * let it set a note to allow it explicitly.
          * Otherwise, a return code that is neither reserved nor HTTP
          * is a bug, as in PR#31759.

     charset_dir_t *dc = ap_get_module_config(r->per_dir_config,
                                              &charset_lite_module);
     charset_req_t *reqinfo;
     charset_filter_ctx_t *input_ctx, *output_ctx;
     apr_status_t rv;
 
-    if (dc->debug >= DBGLVL_FLOW) {
-        ap_log_rerror(APLOG_MARK,APLOG_DEBUG, 0, r,
-                      "uri: %s file: %s method: %d "
-                      "imt: %s flags: %s%s%s %s->%s",
-                      r->uri,
-                      r->filename ? r->filename : "(none)",
-                      r->method_number,
-                      r->content_type ? r->content_type : "(unknown)",
-                      r->main     ? "S" : "",    /* S if subrequest */
-                      r->prev     ? "R" : "",    /* R if redirect */
-                      r->proxyreq ? "P" : "",    /* P if proxy */
-                      dc->charset_source, dc->charset_default);
-    }
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
+                  "uri: %s file: %s method: %d "
+                  "imt: %s flags: %s%s%s %s->%s",
+                  r->uri,
+                  r->filename ? r->filename : "(none)",
+                  r->method_number,
+                  r->content_type ? r->content_type : "(unknown)",
+                  r->main     ? "S" : "",    /* S if subrequest */
+                  r->prev     ? "R" : "",    /* R if redirect */
+                  r->proxyreq ? "P" : "",    /* P if proxy */
+                  dc->charset_source, dc->charset_default);
 
     /* If we don't have a full directory configuration, bail out.
      */
     if (!dc->charset_source || !dc->charset_default) {
-        if (dc->debug >= DBGLVL_PMC) {
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                          "incomplete configuration: src %s, dst %s",
-                          dc->charset_source ? dc->charset_source : "unspecified",
-                          dc->charset_default ? dc->charset_default : "unspecified");
-        }
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01448)
+                      "incomplete configuration: src %s, dst %s",
+                      dc->charset_source ? dc->charset_source : "unspecified",
+                      dc->charset_default ? dc->charset_default : "unspecified");
         return DECLINED;
     }
 
     /* catch proxy requests */
     if (r->proxyreq) {
         return DECLINED;

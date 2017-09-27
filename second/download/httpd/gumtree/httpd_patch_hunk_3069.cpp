 
     if (   (*status == OK)
         && (req_conf = ap_get_module_config(r->request_config,
                                             &proxy_scgi_module))) {
         switch (req_conf->type) {
         case scgi_internal_redirect:
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                          "proxy: " PROXY_FUNCTION ": Internal redirect to %s",
-                          req_conf->location);
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00862)
+                          "Internal redirect to %s", req_conf->location);
 
             r->status_line = NULL;
             if (r->method_number != M_GET) {
                 /* keep HEAD, which is passed around as M_GET, too */
                 r->method = "GET";
                 r->method_number = M_GET;

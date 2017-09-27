     const char *t;
 
     if (!(t = ap_auth_type(r)) || strcasecmp(t, "Basic"))
         return DECLINED;
 
     if (!ap_auth_name(r)) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR,
-                      0, r, APLOGNO(00572) "need AuthName: %s", r->uri);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00572) 
+                      "need AuthName: %s", r->uri);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     if (!auth_line) {
         ap_note_auth_failure(r);
         return HTTP_UNAUTHORIZED;

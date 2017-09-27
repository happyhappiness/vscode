      * when the administrator has full control over the source website. When
      * in forward-proxy mode, websites are public by definition, and so can
      * never be secure. Abort the auth attempt in this case.
      */
     if (PROXYREQ_PROXY == r->proxyreq) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR,
-                      0, r, LOG_PREFIX "form auth cannot be used for proxy "
+                      0, r, APLOGNO(01809) "form auth cannot be used for proxy "
                       "requests due to XSS risk, access denied: %s", r->uri);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     /* We need an authentication realm. */
     if (!ap_auth_name(r)) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR,
-                      0, r, LOG_PREFIX "need AuthName: %s", r->uri);
+                      0, r, APLOGNO(01810) "need AuthName: %s", r->uri);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     r->ap_auth_type = (char *) current_auth;
 
     /* try get the username and password from the notes, if present */

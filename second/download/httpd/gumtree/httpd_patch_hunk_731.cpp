     const char *key;
     apr_ssize_t klen;
 
     BOOL conflict = FALSE;
 
     /*
-     * Give out warnings when a server has HTTPS configured 
+     * Give out warnings when a server has HTTPS configured
      * for the HTTP port or vice versa
      */
     for (s = base_server; s; s = s->next) {
         sc = mySrvConfig(s);
 
-        if (sc->enabled && (s->port == DEFAULT_HTTP_PORT)) {
+        if ((sc->enabled == SSL_ENABLED_TRUE) && (s->port == DEFAULT_HTTP_PORT)) {
             ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                          base_server,
                          "Init: (%s) You configured HTTPS(%d) "
                          "on the standard HTTP(%d) port!",
                          ssl_util_vhostid(p, s),
                          DEFAULT_HTTPS_PORT, DEFAULT_HTTP_PORT);
         }
 
-        if (!sc->enabled && (s->port == DEFAULT_HTTPS_PORT)) {
+        if ((sc->enabled == SSL_ENABLED_FALSE) && (s->port == DEFAULT_HTTPS_PORT)) {
             ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                          base_server,
                          "Init: (%s) You configured HTTP(%d) "
                          "on the standard HTTPS(%d) port!",
                          ssl_util_vhostid(p, s),
                          DEFAULT_HTTP_PORT, DEFAULT_HTTPS_PORT);

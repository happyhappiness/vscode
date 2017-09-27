 {
     SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
 
     SSLConnRec *sslconn = ssl_init_connection_ctx(c);
 
     if (!sc->proxy_enabled) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
-                     "SSL Proxy requested for %s but not enabled "
-                     "[Hint: SSLProxyEngine]", sc->vhost_id);
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
+                      "SSL Proxy requested for %s but not enabled "
+                      "[Hint: SSLProxyEngine]", sc->vhost_id);
 
         return 0;
     }
 
     sslconn->is_proxy = 1;
     sslconn->disabled = 0;

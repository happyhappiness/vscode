 int ssl_engine_disable(conn_rec *c)
 {
     SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
 
     SSLConnRec *sslconn;
 
-    if (!sc->enabled) {
+    if (sc->enabled == SSL_ENABLED_FALSE) {
         return 0;
     }
 
     sslconn = ssl_init_connection_ctx(c);
 
     sslconn->disabled = 1;
 
     return 1;
 }
 
-static int ssl_hook_pre_connection(conn_rec *c, void *csd)
+int ssl_init_ssl_connection(conn_rec *c)
 {
     SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
     SSL *ssl;
     SSLConnRec *sslconn = myConnConfig(c);
     char *vhost_md5;
     modssl_ctx_t *mctx;
 
     /*
-     * Immediately stop processing if SSL is disabled for this connection
+     * Seed the Pseudo Random Number Generator (PRNG)
      */
-    if (!(sc && (sc->enabled ||
-                 (sslconn && sslconn->is_proxy))))
-    {
-        return DECLINED;
-    }
+    ssl_rand_seed(c->base_server, c->pool, SSL_RSCTX_CONNECT, "");
 
-    /*
-     * Create SSL context
-     */
     if (!sslconn) {
         sslconn = ssl_init_connection_ctx(c);
     }
 
-    if (sslconn->disabled) {
-        return DECLINED;
-    }
-
-    /*
-     * Remember the connection information for
-     * later access inside callback functions
-     */
-
-    ap_log_error(APLOG_MARK, APLOG_INFO, 0, c->base_server,
-                 "Connection to child %ld established "
-                 "(server %s, client %s)", c->id, sc->vhost_id, 
-                 c->remote_ip ? c->remote_ip : "unknown");
-
-    /*
-     * Seed the Pseudo Random Number Generator (PRNG)
-     */
-    ssl_rand_seed(c->base_server, c->pool, SSL_RSCTX_CONNECT, "");
-
     mctx = sslconn->is_proxy ? sc->proxy : sc->server;
 
     /*
      * Create a new SSL connection with the configured server SSL context and
      * attach this to the socket. Additionally we register this attachment
      * so we can detach later.
      */
     if (!(ssl = SSL_new(mctx->ssl_ctx))) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
-                     "Unable to create a new SSL connection from the SSL "
-                     "context");
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
+                      "Unable to create a new SSL connection from the SSL "
+                      "context");
         ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
 
         c->aborted = 1;
 
         return DECLINED; /* XXX */
     }
 
     vhost_md5 = ap_md5_binary(c->pool, (unsigned char *)sc->vhost_id,
                               sc->vhost_id_len);
 
     if (!SSL_set_session_id_context(ssl, (unsigned char *)vhost_md5,
-                                    MD5_DIGESTSIZE*2))
+                                    APR_MD5_DIGESTSIZE*2))
     {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
-                     "Unable to set session id context to `%s'", vhost_md5);
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
+                      "Unable to set session id context to `%s'", vhost_md5);
         ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
 
         c->aborted = 1;
 
         return DECLINED; /* XXX */
     }

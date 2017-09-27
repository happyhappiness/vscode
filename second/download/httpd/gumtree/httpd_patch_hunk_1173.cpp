 
     return 1;
 }
 
 int ssl_init_ssl_connection(conn_rec *c)
 {
-    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
+    SSLSrvConfigRec *sc;
     SSL *ssl;
     SSLConnRec *sslconn = myConnConfig(c);
     char *vhost_md5;
     modssl_ctx_t *mctx;
-
-    /*
-     * Seed the Pseudo Random Number Generator (PRNG)
-     */
-    ssl_rand_seed(c->base_server, c->pool, SSL_RSCTX_CONNECT, "");
+    server_rec *server;
 
     if (!sslconn) {
         sslconn = ssl_init_connection_ctx(c);
     }
+    server = sslconn->server;
+    sc = mySrvConfig(server);
+
+    /*
+     * Seed the Pseudo Random Number Generator (PRNG)
+     */
+    ssl_rand_seed(server, c->pool, SSL_RSCTX_CONNECT, "");
 
     mctx = sslconn->is_proxy ? sc->proxy : sc->server;
 
     /*
      * Create a new SSL connection with the configured server SSL context and
      * attach this to the socket. Additionally we register this attachment
      * so we can detach later.
      */
     if (!(ssl = SSL_new(mctx->ssl_ctx))) {
         ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                       "Unable to create a new SSL connection from the SSL "
                       "context");
-        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
+        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, server);
 
         c->aborted = 1;
 
         return DECLINED; /* XXX */
     }
 

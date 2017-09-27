 
     ssl_io_filter_init(c, ssl);
 
     return APR_SUCCESS;
 }
 
-static const char *ssl_hook_http_method(const request_rec *r)
+static const char *ssl_hook_http_scheme(const request_rec *r)
 {
     SSLSrvConfigRec *sc = mySrvConfig(r->server);
 
-    if (sc->enabled == FALSE) {
+    if (sc->enabled == SSL_ENABLED_FALSE || sc->enabled == SSL_ENABLED_OPTIONAL) {
         return NULL;
     }
 
     return "https";
 }
 
 static apr_port_t ssl_hook_default_port(const request_rec *r)
 {
     SSLSrvConfigRec *sc = mySrvConfig(r->server);
 
-    if (sc->enabled == FALSE) {
+    if (sc->enabled == SSL_ENABLED_FALSE || sc->enabled == SSL_ENABLED_OPTIONAL) {
         return 0;
     }
 
     return 443;
 }
 
+static int ssl_hook_pre_connection(conn_rec *c, void *csd)
+{
+    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
+    SSLConnRec *sslconn = myConnConfig(c);
+
+    /*
+     * Immediately stop processing if SSL is disabled for this connection
+     */
+    if (!(sc && (sc->enabled == SSL_ENABLED_TRUE ||
+                 (sslconn && sslconn->is_proxy))))
+    {
+        return DECLINED;
+    }
+
+    /*
+     * Create SSL context
+     */
+    if (!sslconn) {
+        sslconn = ssl_init_connection_ctx(c);
+    }
+
+    if (sslconn->disabled) {
+        return DECLINED;
+    }
+
+    /*
+     * Remember the connection information for
+     * later access inside callback functions
+     */
+
+    ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
+                  "Connection to child %ld established "
+                  "(server %s)", c->id, sc->vhost_id);
+
+    return ssl_init_ssl_connection(c);
+}
+
+
+static void ssl_hook_Insert_Filter(request_rec *r)
+{
+    SSLSrvConfigRec *sc = mySrvConfig(r->server);
+
+    if (sc->enabled == SSL_ENABLED_OPTIONAL) {
+        ap_add_output_filter("UPGRADE_FILTER", NULL, r, r->connection);
+    }
+}
+
 /*
  *  the module registration phase
  */
 
 static void ssl_register_hooks(apr_pool_t *p)
 {
     /* ssl_hook_ReadReq needs to use the BrowserMatch settings so must
-     * run after mod_setenvif's post_read_request hook. */ 
+     * run after mod_setenvif's post_read_request hook. */
     static const char *pre_prr[] = { "mod_setenvif.c", NULL };
 
     ssl_io_filter_register(p);
 
     ap_hook_pre_connection(ssl_hook_pre_connection,NULL,NULL, APR_HOOK_MIDDLE);
+    ap_hook_test_config   (ssl_hook_ConfigTest,    NULL,NULL, APR_HOOK_MIDDLE);
     ap_hook_post_config   (ssl_init_Module,        NULL,NULL, APR_HOOK_MIDDLE);
-    ap_hook_http_method   (ssl_hook_http_method,   NULL,NULL, APR_HOOK_MIDDLE);
+    ap_hook_http_scheme   (ssl_hook_http_scheme,   NULL,NULL, APR_HOOK_MIDDLE);
     ap_hook_default_port  (ssl_hook_default_port,  NULL,NULL, APR_HOOK_MIDDLE);
     ap_hook_pre_config    (ssl_hook_pre_config,    NULL,NULL, APR_HOOK_MIDDLE);
     ap_hook_child_init    (ssl_init_Child,         NULL,NULL, APR_HOOK_MIDDLE);
     ap_hook_check_user_id (ssl_hook_UserCheck,     NULL,NULL, APR_HOOK_FIRST);
     ap_hook_fixups        (ssl_hook_Fixup,         NULL,NULL, APR_HOOK_MIDDLE);
     ap_hook_access_checker(ssl_hook_Access,        NULL,NULL, APR_HOOK_MIDDLE);
     ap_hook_auth_checker  (ssl_hook_Auth,          NULL,NULL, APR_HOOK_MIDDLE);
     ap_hook_post_read_request(ssl_hook_ReadReq, pre_prr,NULL, APR_HOOK_MIDDLE);
+    ap_hook_insert_filter (ssl_hook_Insert_Filter, NULL,NULL, APR_HOOK_MIDDLE);
+/*    ap_hook_handler       (ssl_hook_Upgrade,       NULL,NULL, APR_HOOK_MIDDLE); */
 
     ssl_var_register();
 
     APR_REGISTER_OPTIONAL_FN(ssl_proxy_enable);
     APR_REGISTER_OPTIONAL_FN(ssl_engine_disable);
+
+    APR_REGISTER_OPTIONAL_FN(ssl_extlist_by_oid);
 }
 
 module AP_MODULE_DECLARE_DATA ssl_module = {
     STANDARD20_MODULE_STUFF,
     ssl_config_perdir_create,   /* create per-dir    config structures */
     ssl_config_perdir_merge,    /* merge  per-dir    config structures */

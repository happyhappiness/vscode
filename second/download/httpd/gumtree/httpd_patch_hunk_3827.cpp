         else {
             ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02645)
                           "Server name not provided via TLS extension "
                           "(using default/first virtual host)");
         }
     }
+    
+    return APR_NOTFOUND;
+}
 
-    return SSL_TLSEXT_ERR_NOACK;
+/*
+ * This callback function is executed when OpenSSL encounters an extended
+ * client hello with a server name indication extension ("SNI", cf. RFC 6066).
+ */
+int ssl_callback_ServerNameIndication(SSL *ssl, int *al, modssl_ctx_t *mctx)
+{
+    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
+    apr_status_t status = init_vhost(c, ssl);
+    
+    return (status == APR_SUCCESS)? SSL_TLSEXT_ERR_OK : SSL_TLSEXT_ERR_NOACK;
 }
 
 /*
  * Find a (name-based) SSL virtual host where either the ServerName
  * or one of the ServerAliases matches the supplied name (to be used
  * with ap_vhost_iterate_given_conn())
  */
 static int ssl_find_vhost(void *servername, conn_rec *c, server_rec *s)
 {
     SSLSrvConfigRec *sc;
     SSL *ssl;
-    BOOL found = FALSE;
-    apr_array_header_t *names;
-    int i;
+    BOOL found;
     SSLConnRec *sslcon;
 
-    /* check ServerName */
-    if (!strcasecmp(servername, s->server_hostname)) {
-        found = TRUE;
-    }
-
-    /*
-     * if not matched yet, check ServerAlias entries
-     * (adapted from vhost.c:matches_aliases())
-     */
-    if (!found) {
-        names = s->names;
-        if (names) {
-            char **name = (char **)names->elts;
-            for (i = 0; i < names->nelts; ++i) {
-                if (!name[i])
-                    continue;
-                if (!strcasecmp(servername, name[i])) {
-                    found = TRUE;
-                    break;
-                }
-            }
-        }
-    }
-
-    /* if still no match, check ServerAlias entries with wildcards */
-    if (!found) {
-        names = s->wild_names;
-        if (names) {
-            char **name = (char **)names->elts;
-            for (i = 0; i < names->nelts; ++i) {
-                if (!name[i])
-                    continue;
-                if (!ap_strcasecmp_match(servername, name[i])) {
-                    found = TRUE;
-                    break;
-                }
-            }
-        }
-    }
+    found = ssl_util_vhost_matches(servername, s);
 
     /* set SSL_CTX (if matched) */
     sslcon = myConnConfig(c);
     if (found && (ssl = sslcon->ssl) &&
         (sc = mySrvConfig(s))) {
         SSL_CTX *ctx = SSL_set_SSL_CTX(ssl, sc->server->ssl_ctx);

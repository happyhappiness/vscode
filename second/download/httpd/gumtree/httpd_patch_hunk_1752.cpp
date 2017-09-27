     if ((sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE) &&
         !sslconn->client_cert)
     {
         ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                       "No acceptable peer certificate available");
 
-        return ssl_filter_io_shutdown(filter_ctx, c, 1);
+        ssl_filter_io_shutdown(filter_ctx, c, 1);
+        return APR_ECONNABORTED;
     }
 
     return APR_SUCCESS;
 }
 
-#define SWITCH_STATUS_LINE "HTTP/1.1 101 Switching Protocols"
-#define UPGRADE_HEADER "Upgrade: TLS/1.0, HTTP/1.1"
-#define CONNECTION_HEADER "Connection: Upgrade"
-
-static apr_status_t ssl_io_filter_Upgrade(ap_filter_t *f,
-                                          apr_bucket_brigade *bb)
-{
-    const char *upgrade;
-    apr_bucket_brigade *upgradebb;
-    request_rec *r = f->r;
-    SSLConnRec *sslconn;
-    apr_status_t rv;
-    apr_bucket *b;
-    SSL *ssl;
-
-    /* Just remove the filter, if it doesn't work the first time, it won't
-     * work at all for this request.
-     */
-    ap_remove_output_filter(f);
-
-    /* No need to ensure that this is a server with optional SSL, the filter
-     * is only inserted if that is true.
-     */
-
-    upgrade = apr_table_get(r->headers_in, "Upgrade");
-    if (upgrade == NULL
-        || strcmp(ap_getword(r->pool, &upgrade, ','), "TLS/1.0")) {
-        /* "Upgrade: TLS/1.0, ..." header not found, don't do Upgrade */
-        return ap_pass_brigade(f->next, bb);
-    }
-
-    apr_table_unset(r->headers_out, "Upgrade");
-
-    /* Send the interim 101 response. */
-    upgradebb = apr_brigade_create(r->pool, f->c->bucket_alloc);
-
-    ap_fputstrs(f->next, upgradebb, SWITCH_STATUS_LINE, CRLF,
-                UPGRADE_HEADER, CRLF, CONNECTION_HEADER, CRLF, CRLF, NULL);
-
-    b = apr_bucket_flush_create(f->c->bucket_alloc);
-    APR_BRIGADE_INSERT_TAIL(upgradebb, b);
-
-    rv = ap_pass_brigade(f->next, upgradebb);
-    if (rv) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                      "could not send interim 101 Upgrade response");
-        return AP_FILTER_ERROR;
-    }
-
-    ssl_init_ssl_connection(f->c);
-
-    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
-                  "Awaiting re-negotiation handshake");
-
-    sslconn = myConnConfig(f->c);
-    ssl = sslconn->ssl;
-
-    /* XXX: Should replace SSL_set_state with SSL_renegotiate(ssl);
-     * However, this causes failures in perl-framework currently,
-     * perhaps pre-test if we have already negotiated?
-     */
-    SSL_set_accept_state(ssl);
-    SSL_do_handshake(ssl);
-
-    if (SSL_get_state(ssl) != SSL_ST_OK) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                      "TLS Upgrade handshake failed: "
-                      "Not accepted by client!?");
-
-        return AP_FILTER_ERROR;
-    }
-
-    /* Now that we have initialized the ssl connection which added the ssl_io_filter,
-       pass the brigade off to the connection based output filters so that the
-       request can complete encrypted */
-    return ap_pass_brigade(f->c->output_filters, bb);
-
-}
-
 static apr_status_t ssl_io_filter_input(ap_filter_t *f,
                                         apr_bucket_brigade *bb,
                                         ap_input_mode_t mode,
                                         apr_read_type_e block,
                                         apr_off_t readbytes)
 {
     apr_status_t status;
     bio_filter_in_ctx_t *inctx = f->ctx;
-
-    apr_size_t len = sizeof(inctx->buffer);
+    const char *start = inctx->buffer; /* start of block to return */
+    apr_size_t len = sizeof(inctx->buffer); /* length of block to return */
     int is_init = (mode == AP_MODE_INIT);
 
     if (f->c->aborted) {
         /* XXX: Ok, if we aborted, we ARE at the EOS.  We also have
          * aborted.  This 'double protection' is probably redundant,
          * but also effective against just about anything.

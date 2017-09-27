         return APR_EGENERAL;
     }
     return APR_SUCCESS;
 }
 
 static int hc_get_backend(const char *proxy_function, proxy_conn_rec **backend,
-                          proxy_worker *hc, sctx_t *ctx)
+                          proxy_worker *hc, sctx_t *ctx, apr_pool_t *ptemp)
 {
     int status;
     status = ap_proxy_acquire_connection(proxy_function, backend, hc, ctx->s);
     if (status == OK) {
         (*backend)->addr = hc->cp->addr;
-        (*backend)->pool = ctx->p;
         (*backend)->hostname = hc->s->hostname;
         if (strcmp(hc->s->scheme, "https") == 0) {
             if (!ap_proxy_ssl_enable(NULL)) {
                 ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ctx->s, APLOGNO(03252)
                               "mod_ssl not configured?");
                 return !OK;
             }
             (*backend)->is_ssl = 1;
         }
 
     }
-    status = hc_determine_connection(ctx, hc);
-    if (status == OK) {
-        (*backend)->addr = hc->cp->addr;
-    }
-    return status;
+    return hc_determine_connection(ctx, hc, &(*backend)->addr, ptemp);
 }
 
-static apr_status_t hc_check_tcp(sctx_t *ctx, apr_pool_t *ptemp, proxy_worker *worker)
+static apr_status_t hc_check_tcp(baton_t *baton)
 {
     int status;
+    sctx_t *ctx = baton->ctx;
+    proxy_worker *hc = baton->hc;
     proxy_conn_rec *backend = NULL;
-    proxy_worker *hc;
 
-    hc = hc_get_hcworker(ctx, worker, ptemp);
-
-    status = hc_get_backend("HCTCP", &backend, hc, ctx);
+    status = hc_get_backend("HCTCP", &backend, hc, ctx, baton->ptemp);
     if (status == OK) {
         backend->addr = hc->cp->addr;
         status = ap_proxy_connect_backend("HCTCP", backend, hc, ctx->s);
         /* does an unconditional ap_proxy_is_socket_connected() */
     }
     return backend_cleanup("HCTCP", backend, ctx->s, status);
 }
 
-static void hc_send(sctx_t *ctx, apr_pool_t *ptemp, const char *out, proxy_conn_rec *backend)
+static int hc_send(request_rec *r, const char *out, apr_bucket_brigade *bb)
 {
-    apr_bucket_brigade *tmp_bb = apr_brigade_create(ptemp, ctx->ba);
-    ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, ctx->s, "%s", out);
-    APR_BRIGADE_INSERT_TAIL(tmp_bb, apr_bucket_pool_create(out, strlen(out), ptemp,
-                            ctx->ba));
-    APR_BRIGADE_INSERT_TAIL(tmp_bb, apr_bucket_flush_create(ctx->ba));
-    ap_pass_brigade(backend->connection->output_filters, tmp_bb);
-    apr_brigade_destroy(tmp_bb);
+    apr_status_t rv;
+    conn_rec *c = r->connection;
+    apr_bucket_alloc_t *ba = c->bucket_alloc;
+    ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, r->server, "%s", out);
+    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(out, strlen(out),
+                                                       r->pool, ba));
+    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_flush_create(ba));
+    rv = ap_pass_brigade(c->output_filters, bb);
+    apr_brigade_cleanup(bb);
+    return (rv) ? !OK : OK;
 }
 
-static int hc_read_headers(sctx_t *ctx, request_rec *r)
+static int hc_read_headers(request_rec *r)
 {
     char buffer[HUGE_STRING_LEN];
     int len;
 
     len = ap_getline(buffer, sizeof(buffer), r, 1);
     if (len <= 0) {
         return !OK;
     }
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03254)
-            "%s", buffer);
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(03254)
+                 "%.*s", len, buffer);
     /* for the below, see ap_proxy_http_process_response() */
     if (apr_date_checkmask(buffer, "HTTP/#.# ###*")) {
         int major;
         char keepchar;
         int proxy_status = OK;
         const char *proxy_status_line = NULL;

     } else {
         return !OK;
     }
     /* OK, 1st line is OK... scarf in the headers */
     while ((len = ap_getline(buffer, sizeof(buffer), r, 1)) > 0) {
         char *value, *end;
+        ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, r->server, "%.*s",
+                     len, buffer);
         if (!(value = strchr(buffer, ':'))) {
             return !OK;
         }
-        ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, ctx->s, "%s", buffer);
         *value = '\0';
         ++value;
         while (apr_isspace(*value))
             ++value;            /* Skip to start of value   */
         for (end = &value[strlen(value)-1]; end > value && apr_isspace(*end); --end)
             *end = '\0';
         apr_table_add(r->headers_out, buffer, value);
     }
     return OK;
 }
 
-static int hc_read_body (sctx_t *ctx, request_rec *r)
+static int hc_read_body(request_rec *r, apr_bucket_brigade *bb)
 {
     apr_status_t rv = APR_SUCCESS;
-    apr_bucket_brigade *bb;
     int seen_eos = 0;
 
-    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
     do {
-        apr_bucket *bucket, *cpy;
         apr_size_t len = HUGE_STRING_LEN;
 
+        apr_brigade_cleanup(bb);
         rv = ap_get_brigade(r->proto_input_filters, bb, AP_MODE_READBYTES,
                             APR_BLOCK_READ, len);
 
         if (rv != APR_SUCCESS) {
-            if (APR_STATUS_IS_TIMEUP(rv) || APR_STATUS_IS_EOF(rv)) {
+            if (APR_STATUS_IS_EOF(rv)) {
                 rv = APR_SUCCESS;
                 break;
             }
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ctx->s, APLOGNO(03300)
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server, APLOGNO(03300)
                           "Error reading response body");
             break;
         }
 
-        for (bucket = APR_BRIGADE_FIRST(bb);
-             bucket != APR_BRIGADE_SENTINEL(bb);
-             bucket = APR_BUCKET_NEXT(bucket))
-        {
+        while (!APR_BRIGADE_EMPTY(bb)) {
+            apr_bucket *bucket = APR_BRIGADE_FIRST(bb);
             if (APR_BUCKET_IS_EOS(bucket)) {
                 seen_eos = 1;
                 break;
             }
             if (APR_BUCKET_IS_FLUSH(bucket)) {
+                apr_bucket_delete(bucket);
                 continue;
             }
-            rv =  apr_bucket_copy(bucket, &cpy);
-            if (rv != APR_SUCCESS) {
-                break;
-            }
-            APR_BRIGADE_INSERT_TAIL(r->kept_body, cpy);
+            APR_BUCKET_REMOVE(bucket);
+            APR_BRIGADE_INSERT_TAIL(r->kept_body, bucket);
         }
-        apr_brigade_cleanup(bb);
     }
     while (!seen_eos);
+    apr_brigade_cleanup(bb);
     return (rv == APR_SUCCESS ? OK : !OK);
 }
 
 /*
  * Send the HTTP OPTIONS, HEAD or GET request to the backend
  * server associated w/ worker. If we have Conditions,
  * then apply those to the resulting response, otherwise
  * any status code 2xx or 3xx is considered "passing"
  */
-static apr_status_t hc_check_http(sctx_t *ctx, apr_pool_t *ptemp, proxy_worker *worker)
+static apr_status_t hc_check_http(baton_t *baton)
 {
     int status;
     proxy_conn_rec *backend = NULL;
-    proxy_worker *hc;
-    conn_rec c;
+    sctx_t *ctx = baton->ctx;
+    proxy_worker *hc = baton->hc;
+    proxy_worker *worker = baton->worker;
+    apr_pool_t *ptemp = baton->ptemp;
     request_rec *r;
     wctx_t *wctx;
     hc_condition_t *cond;
-    const char *method = NULL;
+    apr_bucket_brigade *bb;
 
-    hc = hc_get_hcworker(ctx, worker, ptemp);
     wctx = (wctx_t *)hc->context;
+    if (!wctx->req || !wctx->method) {
+        return APR_ENOTIMPL;
+    }
 
-    if ((status = hc_get_backend("HCOH", &backend, hc, ctx)) != OK) {
+    if ((status = hc_get_backend("HCOH", &backend, hc, ctx, ptemp)) != OK) {
         return backend_cleanup("HCOH", backend, ctx->s, status);
     }
     if ((status = ap_proxy_connect_backend("HCOH", backend, hc, ctx->s)) != OK) {
         return backend_cleanup("HCOH", backend, ctx->s, status);
     }
 
     if (!backend->connection) {
-        if ((status = ap_proxy_connection_create("HCOH", backend, &c, ctx->s)) != OK) {
+        if ((status = ap_proxy_connection_create("HCOH", backend, NULL, ctx->s)) != OK) {
             return backend_cleanup("HCOH", backend, ctx->s, status);
         }
     }
-    switch (hc->s->method) {
-        case OPTIONS:
-            if (!wctx->req) {
-                wctx->req = apr_psprintf(ctx->p,
-                                   "OPTIONS * HTTP/1.0\r\nHost: %s:%d\r\n\r\n",
-                                    hc->s->hostname, (int)hc->s->port);
-            }
-            method = "OPTIONS";
-            break;
 
-        case HEAD:
-            method = "HEAD";
-            /* fallthru */
-        case GET:
-            if (!method) { /* did we fall thru? If not, we are GET */
-                method = "GET";
-            }
-            if (!wctx->req) {
-                wctx->req = apr_psprintf(ctx->p,
-                                   "%s %s%s%s HTTP/1.0\r\nHost: %s:%d\r\n\r\n",
-                                   method,
-                                   (wctx->path ? wctx->path : ""),
-                                   (wctx->path && *hc->s->hcuri ? "/" : "" ),
-                                   (*hc->s->hcuri ? hc->s->hcuri : ""),
-                                   hc->s->hostname, (int)hc->s->port);
-            }
-            break;
+    r = create_request_rec(ptemp, backend->connection, wctx->method);
+    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
 
-        default:
-            return backend_cleanup("HCOH", backend, ctx->s, !OK);
-            break;
+    if ((status = hc_send(r, wctx->req, bb)) != OK) {
+        return backend_cleanup("HCOH", backend, ctx->s, status);
     }
-
-    hc_send(ctx, ptemp, wctx->req, backend);
-
-    r = create_request_rec(ptemp, backend->connection, method);
-    if ((status = hc_read_headers(ctx, r)) != OK) {
+    if ((status = hc_read_headers(r)) != OK) {
         return backend_cleanup("HCOH", backend, ctx->s, status);
     }
-    if (hc->s->method == GET) {
-        if ((status = hc_read_body(ctx, r)) != OK) {
+    if (!r->header_only) {
+        apr_table_t *saved_headers_in = r->headers_in;
+        r->headers_in = apr_table_copy(r->pool, r->headers_out);
+        ap_proxy_pre_http_request(backend->connection, r);
+        status = hc_read_body(r, bb);
+        r->headers_in = saved_headers_in;
+        if (status != OK) {
             return backend_cleanup("HCOH", backend, ctx->s, status);
         }
+        r->trailers_out = apr_table_copy(r->pool, r->trailers_in);
     }
 
     if (*worker->s->hcexpr &&
             (cond = (hc_condition_t *)apr_table_get(ctx->conditions, worker->s->hcexpr)) != NULL) {
         const char *err;
         int ok = ap_expr_exec(r, cond->pexpr, &err);
         if (ok > 0) {
-            status = OK;
             ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, ctx->s,
                          "Condition %s for %s (%s): passed", worker->s->hcexpr,
                          hc->s->name, worker->s->name);
         } else if (ok < 0 || err) {
-            status = !OK;
             ap_log_error(APLOG_MARK, APLOG_INFO, 0, ctx->s, APLOGNO(03301)
                          "Error on checking condition %s for %s (%s): %s", worker->s->hcexpr,
                          hc->s->name, worker->s->name, err);
+            status = !OK;
         } else {
             ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, ctx->s,
                          "Condition %s for %s (%s) : failed", worker->s->hcexpr,
                          hc->s->name, worker->s->name);
             status = !OK;
         }
     } else if (r->status < 200 || r->status > 399) {
+        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, ctx->s,
+                     "Response status %i for %s (%s): failed", r->status,
+                     hc->s->name, worker->s->name);
         status = !OK;
     }
     return backend_cleanup("HCOH", backend, ctx->s, status);
 }
 
 static void * APR_THREAD_FUNC hc_check(apr_thread_t *thread, void *b)
 {
     baton_t *baton = (baton_t *)b;
-    sctx_t *ctx = baton->ctx;
-    apr_time_t now = baton->now;
+    server_rec *s = baton->ctx->s;
     proxy_worker *worker = baton->worker;
-    apr_pool_t *ptemp = baton->ptemp;
-    server_rec *s = ctx->s;
+    proxy_worker *hc = baton->hc;
+    apr_time_t now = baton->now;
     apr_status_t rv;
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03256)
-                 "%sHealth checking %s", (thread ? "Threaded " : ""), worker->s->name);
-
-    switch (worker->s->method) {
-        case TCP:
-            rv = hc_check_tcp(ctx, ptemp, worker);
-            break;
 
-        case OPTIONS:
-        case HEAD:
-        case GET:
-             rv = hc_check_http(ctx, ptemp, worker);
-             break;
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03256)
+                 "%sHealth checking %s", (thread ? "Threaded " : ""),
+                 worker->s->name);
 
-        default:
-            rv = APR_ENOTIMPL;
-            break;
+    if (hc->s->method == TCP) {
+        rv = hc_check_tcp(baton);
+    }
+    else {
+        rv = hc_check_http(baton);
     }
     if (rv == APR_ENOTIMPL) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(03257)
                          "Somehow tried to use unimplemented hcheck method: %d",
-                         (int)worker->s->method);
-        apr_pool_destroy(ptemp);
+                         (int)hc->s->method);
+        apr_pool_destroy(baton->ptemp);
         return NULL;
     }
     /* what state are we in ? */
     if (PROXY_WORKER_IS_HCFAILED(worker)) {
         if (rv == APR_SUCCESS) {
             worker->s->pcount += 1;

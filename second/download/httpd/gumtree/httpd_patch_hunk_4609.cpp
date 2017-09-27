 
 
     /* Time to populate r with the data we have. */
     r->method = method;
     /* Provide quick information about the request method as soon as known */
     r->method_number = ap_method_number_of(r->method);
-    if (r->method_number == M_GET && r->method[0] == 'G') {
+    if (r->method_number == M_OPTIONS
+            || (r->method_number == M_GET && r->method[0] == 'H')) {
+        r->header_only = 1;
+    }
+    else {
         r->header_only = 0;
     }
 
     r->protocol = "HTTP/1.0";
     r->proto_num = HTTP_VERSION(1, 0);
 
     r->hostname = NULL;
 
     return r;
 }
 
+static void create_hcheck_req(wctx_t *wctx, proxy_worker *hc,
+                              apr_pool_t *p)
+{
+    char *req = NULL;
+    const char *method = NULL;
+    switch (hc->s->method) {
+        case OPTIONS:
+            method = "OPTIONS";
+            req = apr_psprintf(p,
+                               "OPTIONS * HTTP/1.0\r\n"
+                               "Host: %s:%d\r\n"
+                               "\r\n",
+                               hc->s->hostname, (int)hc->s->port);
+            break;
+
+        case HEAD:
+            method = "HEAD";
+            /* fallthru */
+        case GET:
+            if (!method) { /* did we fall thru? If not, we are GET */
+                method = "GET";
+            }
+            req = apr_psprintf(p,
+                               "%s %s%s%s HTTP/1.0\r\n"
+                               "Host: %s:%d\r\n"
+                               "\r\n",
+                               method,
+                               (wctx->path ? wctx->path : ""),
+                               (wctx->path && *hc->s->hcuri ? "/" : "" ),
+                               (*hc->s->hcuri ? hc->s->hcuri : ""),
+                               hc->s->hostname, (int)hc->s->port);
+            break;
+
+        default:
+            break;
+    }
+    wctx->req = req;
+    wctx->method = method;
+}
+
 static proxy_worker *hc_get_hcworker(sctx_t *ctx, proxy_worker *worker,
                                      apr_pool_t *p)
 {
     proxy_worker *hc = NULL;
-    const char* wptr;
     apr_port_t port;
 
-    wptr = apr_psprintf(ctx->p, "%pp", worker);
-    hc = (proxy_worker *)apr_hash_get(ctx->hcworkers, wptr, APR_HASH_KEY_STRING);
-    port = (worker->s->port ? worker->s->port : ap_proxy_port_of_scheme(worker->s->scheme));
+    hc = (proxy_worker *)apr_hash_get(ctx->hcworkers, &worker, sizeof worker);
     if (!hc) {
         apr_uri_t uri;
         apr_status_t rv;
         const char *url = worker->s->name;
         wctx_t *wctx = apr_pcalloc(ctx->p, sizeof(wctx_t));
 
+        port = (worker->s->port ? worker->s->port
+                                : ap_proxy_port_of_scheme(worker->s->scheme));
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03248)
-                     "Creating hc worker %s for %s://%s:%d",
-                     wptr, worker->s->scheme, worker->s->hostname,
+                     "Creating hc worker %pp for %s://%s:%d",
+                     worker, worker->s->scheme, worker->s->hostname,
                      (int)port);
 
         ap_proxy_define_worker(ctx->p, &hc, NULL, NULL, worker->s->name, 0);
-        PROXY_STRNCPY(hc->s->name,     wptr);
+        apr_snprintf(hc->s->name, sizeof hc->s->name, "%pp", worker);
         PROXY_STRNCPY(hc->s->hostname, worker->s->hostname);
         PROXY_STRNCPY(hc->s->scheme,   worker->s->scheme);
         PROXY_STRNCPY(hc->s->hcuri,    worker->s->hcuri);
         PROXY_STRNCPY(hc->s->hcexpr,   worker->s->hcexpr);
         hc->hash.def = hc->s->hash.def = ap_proxy_hashfunc(hc->s->name, PROXY_HASHFUNC_DEFAULT);
         hc->hash.fnv = hc->s->hash.fnv = ap_proxy_hashfunc(hc->s->name, PROXY_HASHFUNC_FNV);

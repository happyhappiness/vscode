     }
     else if (ccfg->timeout_at == 0) {
         /* no timeout set */
         return ap_get_brigade(f->next, bb, mode, block, readbytes);
     }
 
-    time_left = ccfg->timeout_at - now;
-    if (time_left <= 0) {
-        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
-                      "Request %s read timeout", ccfg->type);
-        return APR_TIMEUP;
+    if (!ccfg->socket) {
+        ccfg->socket = ap_get_module_config(f->c->conn_config, &core_module);
     }
 
+    rv = check_time_left(ccfg, &time_left);
+    if (rv != APR_SUCCESS)
+        goto out;
+
     if (block == APR_NONBLOCK_READ || mode == AP_MODE_INIT
         || mode == AP_MODE_EATCRLF) {
         rv = ap_get_brigade(f->next, bb, mode, block, readbytes);
         if (ccfg->min_rate > 0 && rv == APR_SUCCESS) {
             extend_timeout(ccfg, bb);
         }
         return rv;
     }
 
-    if (time_left < apr_time_from_sec(1)) {
-        time_left = apr_time_from_sec(1);
-    }
+    rv = apr_socket_timeout_get(ccfg->socket, &saved_sock_timeout);
+    AP_DEBUG_ASSERT(rv == APR_SUCCESS);
 
-    rv = apr_socket_timeout_get(ctx->socket, &saved_sock_timeout);
+    rv = apr_socket_timeout_set(ccfg->socket, MIN(time_left, saved_sock_timeout));
     AP_DEBUG_ASSERT(rv == APR_SUCCESS);
 
-    if (saved_sock_timeout >= time_left) {
-        rv = apr_socket_timeout_set(ctx->socket, time_left);
-        AP_DEBUG_ASSERT(rv == APR_SUCCESS);
-    }
-    else {
-        saved_sock_timeout = -1;
-    }
+    if (mode == AP_MODE_GETLINE) {
+        /*
+         * For a blocking AP_MODE_GETLINE read, apr_brigade_split_line()
+         * would loop until a whole line has been read. As this would make it
+         * impossible to enforce a total timeout, we only do non-blocking
+         * reads.
+         */
+        apr_off_t remaining = HUGE_STRING_LEN;
+        do {
+            apr_off_t bblen;
+#if APR_MAJOR_VERSION < 2
+            apr_int32_t nsds;
+            apr_interval_time_t poll_timeout;
+            apr_pollfd_t pollset;
+#endif
+
+            rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE, APR_NONBLOCK_READ, remaining);
+            if (rv != APR_SUCCESS && !APR_STATUS_IS_EAGAIN(rv)) {
+                break;
+            }
+
+            if (!APR_BRIGADE_EMPTY(bb)) {
+                if (ccfg->min_rate > 0) {
+                    extend_timeout(ccfg, bb);
+                }
+
+                rv = have_lf_or_eos(bb);
+                if (rv != APR_INCOMPLETE) {
+                    break;
+                }
+
+                rv = apr_brigade_length(bb, 1, &bblen);
+                if (rv != APR_SUCCESS) {
+                    break;
+                }
+                remaining -= bblen;
+                if (remaining <= 0) {
+                    break;
+                }
+
+                /* Haven't got a whole line yet, save what we have ... */
+                if (!ccfg->tmpbb) {
+                    ccfg->tmpbb = apr_brigade_create(f->c->pool, f->c->bucket_alloc);
+                }
+                rv = brigade_append(ccfg->tmpbb, bb);
+                if (rv != APR_SUCCESS)
+                    break;
+            }
+
+            /* ... and wait for more */
+#if APR_MAJOR_VERSION < 2
+            pollset.p = f->c->pool;
+            pollset.desc_type = APR_POLL_SOCKET;
+            pollset.reqevents = APR_POLLIN|APR_POLLHUP;
+            pollset.desc.s = ccfg->socket;
+            apr_socket_timeout_get(ccfg->socket, &poll_timeout);
+            rv = apr_poll(&pollset, 1, &nsds, poll_timeout);
+#else
+            rv = apr_socket_wait(ccfg->socket, APR_WAIT_READ);
+#endif
+            if (rv != APR_SUCCESS)
+                break;
+
+            rv = check_time_left(ccfg, &time_left);
+            if (rv != APR_SUCCESS)
+                break;
+
+            rv = apr_socket_timeout_set(ccfg->socket,
+                                   MIN(time_left, saved_sock_timeout));
+            AP_DEBUG_ASSERT(rv == APR_SUCCESS);
 
-    rv = ap_get_brigade(f->next, bb, mode, block, readbytes);
+        } while (1);
 
-    if (saved_sock_timeout != -1) {
-        apr_socket_timeout_set(ctx->socket, saved_sock_timeout);
-    }
+        if (ccfg->tmpbb)
+            APR_BRIGADE_PREPEND(bb, ccfg->tmpbb);
 
-    if (ccfg->min_rate > 0 && rv == APR_SUCCESS) {
-        extend_timeout(ccfg, bb);
+    }
+    else {
+        /* mode != AP_MODE_GETLINE */
+        rv = ap_get_brigade(f->next, bb, mode, block, readbytes);
+        if (ccfg->min_rate > 0 && rv == APR_SUCCESS) {
+            extend_timeout(ccfg, bb);
+        }
     }
 
+    apr_socket_timeout_set(ccfg->socket, saved_sock_timeout);
+
+out:
     if (APR_STATUS_IS_TIMEUP(rv)) {
         ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                       "Request %s read timeout", ccfg->type);
+        /*
+         * If we allow a normal lingering close, the client may keep this
+         * process/thread busy for another 30s (MAX_SECS_TO_LINGER).
+         * Therefore we tell ap_lingering_close() to shorten this period to
+         * 2s (SECONDS_TO_LINGER).
+         */
+        apr_table_setn(f->c->notes, "short-lingering-close", "1");
     }
     return rv;
 }
 
-static int reqtimeout_pre_conn(conn_rec *c, void *csd)
+static int reqtimeout_init(conn_rec *c)
 {
-    reqtimeout_ctx *ctx;
     reqtimeout_con_cfg *ccfg;
     reqtimeout_srv_cfg *cfg;
 
     cfg = ap_get_module_config(c->base_server->module_config,
                                &reqtimeout_module);
     AP_DEBUG_ASSERT(cfg != NULL);
     if (cfg->header_timeout <= 0 && cfg->body_timeout <= 0) {
         /* not configured for this vhost */
-        return OK;
+        return DECLINED;
     }
 
-    ctx = apr_pcalloc(c->pool, sizeof(reqtimeout_ctx));
-    ctx->socket = csd;
-
     ccfg = apr_pcalloc(c->pool, sizeof(reqtimeout_con_cfg));
     ccfg->new_timeout = cfg->header_timeout;
     ccfg->new_max_timeout = cfg->header_max_timeout;
     ccfg->type = "header";
     ccfg->min_rate = cfg->header_min_rate;
     ccfg->rate_factor = cfg->header_rate_factor;
     ap_set_module_config(c->conn_config, &reqtimeout_module, ccfg);
 
-    ap_add_input_filter("reqtimeout", ctx, NULL, c);
-    return OK;
+    ap_add_input_filter("reqtimeout", ccfg, NULL, c);
+    /* we are not handling the connection, we just do initialization */
+    return DECLINED;
 }
 
 static int reqtimeout_after_headers(request_rec *r)
 {
     reqtimeout_srv_cfg *cfg;
     reqtimeout_con_cfg *ccfg =
         ap_get_module_config(r->connection->conn_config, &reqtimeout_module);
 
     if (ccfg == NULL) {
-        /* not configured for this vhost */
+        /* not configured for this connection */
         return OK;
     }
 
     cfg = ap_get_module_config(r->connection->base_server->module_config,
                                &reqtimeout_module);
     AP_DEBUG_ASSERT(cfg != NULL);
 
     ccfg->timeout_at = 0;
     ccfg->max_timeout_at = 0;
-    ccfg->new_timeout = cfg->body_timeout;
-    ccfg->new_max_timeout = cfg->body_max_timeout;
-    ccfg->min_rate = cfg->body_min_rate;
-    ccfg->rate_factor = cfg->body_rate_factor;
-    ccfg->type = "body";
+    if (r->method_number != M_CONNECT) {
+        ccfg->new_timeout = cfg->body_timeout;
+        ccfg->new_max_timeout = cfg->body_max_timeout;
+        ccfg->min_rate = cfg->body_min_rate;
+        ccfg->rate_factor = cfg->body_rate_factor;
+        ccfg->type = "body";
+    }
 
     return OK;
 }
 
 static int reqtimeout_after_body(request_rec *r)
 {
     reqtimeout_srv_cfg *cfg;
     reqtimeout_con_cfg *ccfg =
         ap_get_module_config(r->connection->conn_config, &reqtimeout_module);
 
     if (ccfg == NULL) {
-        /* not configured for this vhost */
+        /* not configured for this connection */
         return OK;
     }
 
     cfg = ap_get_module_config(r->connection->base_server->module_config,
                                &reqtimeout_module);
     AP_DEBUG_ASSERT(cfg != NULL);

     }
 
     apr_socket_timeout_set(ccfg->socket, saved_sock_timeout);
 
 out:
     if (APR_STATUS_IS_TIMEUP(rv)) {
-        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
+        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c, APLOGNO(01382)
                       "Request %s read timeout", ccfg->type);
         /*
          * If we allow a normal lingering close, the client may keep this
          * process/thread busy for another 30s (MAX_SECS_TO_LINGER).
          * Therefore we tell ap_lingering_close() to shorten this period to
          * 2s (SECONDS_TO_LINGER).
          */
         apr_table_setn(f->c->notes, "short-lingering-close", "1");
+
+        /*
+         * Also, we must not allow keep-alive requests, as
+         * ap_finalize_protocol() may ignore our error status (if the timeout
+         * happened on a request body that is discarded).
+         */
+        f->c->keepalive = AP_CONN_CLOSE;
     }
     return rv;
 }
 
 static int reqtimeout_init(conn_rec *c)
 {
     reqtimeout_con_cfg *ccfg;
     reqtimeout_srv_cfg *cfg;
 
     cfg = ap_get_module_config(c->base_server->module_config,
                                &reqtimeout_module);
     AP_DEBUG_ASSERT(cfg != NULL);
-    if (cfg->header_timeout <= 0 && cfg->body_timeout <= 0) {
-        /* not configured for this vhost */
+    if (cfg->header_timeout == 0 && cfg->body_timeout == 0) {
+        /* disabled for this vhost */
         return DECLINED;
     }
 
     ccfg = apr_pcalloc(c->pool, sizeof(reqtimeout_con_cfg));
-    ccfg->new_timeout = cfg->header_timeout;
-    ccfg->new_max_timeout = cfg->header_max_timeout;
     ccfg->type = "header";
-    ccfg->min_rate = cfg->header_min_rate;
-    ccfg->rate_factor = cfg->header_rate_factor;
+    if (cfg->header_timeout != UNSET) {
+        ccfg->new_timeout     = cfg->header_timeout;
+        ccfg->new_max_timeout = cfg->header_max_timeout;
+        ccfg->min_rate        = cfg->header_min_rate;
+        ccfg->rate_factor     = cfg->header_rate_factor;
+    }
+    else {
+        ccfg->new_timeout     = MRT_DEFAULT_HEADER_TIMEOUT;
+        ccfg->new_max_timeout = MRT_DEFAULT_HEADER_MAX_TIMEOUT;
+        ccfg->min_rate        = MRT_DEFAULT_HEADER_MIN_RATE;
+        ccfg->rate_factor     = default_header_rate_factor;
+    }
     ap_set_module_config(c->conn_config, &reqtimeout_module, ccfg);
 
     ap_add_input_filter("reqtimeout", ccfg, NULL, c);
     /* we are not handling the connection, we just do initialization */
     return DECLINED;
 }

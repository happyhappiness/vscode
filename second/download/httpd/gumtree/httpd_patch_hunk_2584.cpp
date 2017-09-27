                 }
                 now = apr_time_sec(apr_time_now());
                 apr_pool_destroy(p);
             }
         break;
         case AP_WATCHDOG_STATE_STOPPING:
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s,
-                         "Heartmonitor: stopping %s listener.",
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(02092)
+                         "stopping %s listener.",
                          HM_WATHCHDOG_NAME);
 
             ctx->keep_running = 0;
             if (ctx->sock) {
                 apr_socket_close(ctx->sock);
                 ctx->sock = NULL;

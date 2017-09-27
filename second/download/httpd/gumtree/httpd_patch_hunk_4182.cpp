              */
             else if (APR_STATUS_IS_EINTR(rv)) {
                 goto worker_pop;
             }
             /* We got some other error. */
             else if (!workers_may_exit) {
-                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
+                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(03139)
                              "ap_queue_pop failed");
             }
             continue;
         }
         is_idle = 0;
         worker_sockets[thread_slot] = csd;

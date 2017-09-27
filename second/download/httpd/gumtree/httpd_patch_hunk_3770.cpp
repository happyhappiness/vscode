                 apr_thread_mutex_lock(timeout_mutex);
                 ap_log_error(APLOG_MARK, APLOG_TRACE6, 0, ap_server_conf,
                              "connections: %u (clogged: %u write-completion: %d "
                              "keep-alive: %d lingering: %d suspended: %u)",
                              apr_atomic_read32(&connection_count),
                              apr_atomic_read32(&clogged_count),
-                             write_completion_q.count,
-                             keepalive_q.count,
+                             *write_completion_q->total,
+                             *keepalive_q->total,
                              apr_atomic_read32(&lingering_count),
                              apr_atomic_read32(&suspended_count));
                 apr_thread_mutex_unlock(timeout_mutex);
             }
         }
 

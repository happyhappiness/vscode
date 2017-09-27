             close_listeners(process_slot, &closed);
             if (terminate_mode == ST_UNGRACEFUL
                 || apr_atomic_read32(&connection_count) == 0)
                 break;
         }
 
-        if (requests_this_child <= 0) {
+        if (conns_this_child <= 0)
             check_infinite_requests();
-        }
 
         now = apr_time_now();
         if (APLOGtrace6(ap_server_conf)) {
             /* trace log status every second */
             if (now - last_log > apr_time_from_msec(1000)) {
                 last_log = now;
                 apr_thread_mutex_lock(timeout_mutex);
                 ap_log_error(APLOG_MARK, APLOG_TRACE6, 0, ap_server_conf,
-                             "connections: %d (write-completion: %d "
-                             "keep-alive: %d lingering: %d)",
-                             connection_count, write_completion_q.count,
+                             "connections: %u (clogged: %u write-completion: %d "
+                             "keep-alive: %d lingering: %d suspended: %u)",
+                             apr_atomic_read32(&connection_count),
+                             apr_atomic_read32(&clogged_count),
+                             write_completion_q.count,
                              keepalive_q.count,
-                             linger_q.count + short_linger_q.count);
+                             apr_atomic_read32(&lingering_count),
+                             apr_atomic_read32(&suspended_count));
                 apr_thread_mutex_unlock(timeout_mutex);
             }
         }
 
         apr_thread_mutex_lock(g_timer_ring_mtx);
         if (!APR_RING_EMPTY(&timer_ring, timer_event_t, link)) {

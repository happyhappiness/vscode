                 ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, ap_server_conf,
                              "All workers are busy, will close %d keep-alive "
                              "connections",
                              keepalive_q.count);
                 process_timeout_queue(&keepalive_q,
                                       timeout_time + ap_server_conf->keep_alive_timeout,
-                                      start_lingering_close);
+                                      start_lingering_close_nonblocking);
             }
             else {
                 process_timeout_queue(&keepalive_q, timeout_time,
-                                      start_lingering_close);
+                                      start_lingering_close_nonblocking);
             }
             /* Step 2: write completion timeouts */
-            process_timeout_queue(&write_completion_q, timeout_time, start_lingering_close);
+            process_timeout_queue(&write_completion_q, timeout_time,
+                                  start_lingering_close_nonblocking);
             /* Step 3: (normal) lingering close completion timeouts */
             process_timeout_queue(&linger_q, timeout_time, stop_lingering_close);
             /* Step 4: (short) lingering close completion timeouts */
             process_timeout_queue(&short_linger_q, timeout_time, stop_lingering_close);
 
             ps = ap_get_scoreboard_process(process_slot);
             ps->write_completion = write_completion_q.count;
-            ps->lingering_close = linger_q.count + short_linger_q.count;
             ps->keep_alive = keepalive_q.count;
             apr_thread_mutex_unlock(timeout_mutex);
 
             ps->connections = apr_atomic_read32(&connection_count);
-            /* XXX: should count CONN_STATE_SUSPENDED and set ps->suspended */
+            ps->suspended = apr_atomic_read32(&suspended_count);
+            ps->lingering_close = apr_atomic_read32(&lingering_count);
         }
-        if (listeners_disabled && !workers_were_busy &&
-            (int)apr_atomic_read32(&connection_count) <
-            ((int)ap_queue_info_get_idlers(worker_queue_info) - 1) *
-            worker_factor / WORKER_FACTOR_SCALE + threads_per_child)
+        if (listeners_disabled && !workers_were_busy
+            && (int)apr_atomic_read32(&connection_count)
+               - (int)apr_atomic_read32(&lingering_count)
+               < ((int)ap_queue_info_get_idlers(worker_queue_info) - 1)
+                 * worker_factor / WORKER_FACTOR_SCALE + threads_per_child)
         {
             listeners_disabled = 0;
             enable_listensocks(process_slot);
         }
         /*
          * XXX: do we need to set some timeout that re-enables the listensocks

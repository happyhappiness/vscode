     /* Unblock the signal used to wake this thread up, and set a handler for
      * it.
      */
     unblock_signal(LISTENER_SIGNAL);
     apr_signal(LISTENER_SIGNAL, dummy_signal_handler);
 
-    while (!listener_may_exit) {
+    for (;;) {
+        int workers_were_busy = 0;
+        if (listener_may_exit) {
+            close_listeners(process_slot, &closed);
+            if (terminate_mode == ST_UNGRACEFUL
+                || apr_atomic_read32(&connection_count) == 0)
+                break;
+        }
 
         if (requests_this_child <= 0) {
             check_infinite_requests();
         }
 
+        now = apr_time_now();
+        if (APLOGtrace6(ap_server_conf)) {
+            /* trace log status every second */
+            if (now - last_log > apr_time_from_msec(1000)) {
+                last_log = now;
+                apr_thread_mutex_lock(timeout_mutex);
+                ap_log_error(APLOG_MARK, APLOG_TRACE6, 0, ap_server_conf,
+                             "connections: %d (write-completion: %d "
+                             "keep-alive: %d lingering: %d)",
+                             connection_count, write_completion_q.count,
+                             keepalive_q.count,
+                             linger_q.count + short_linger_q.count);
+                apr_thread_mutex_unlock(timeout_mutex);
+            }
+        }
 
-        {
-            apr_time_t now = apr_time_now();
-            apr_thread_mutex_lock(g_timer_ring_mtx);
-
-            if (!APR_RING_EMPTY(&timer_ring, timer_event_t, link)) {
-                te = APR_RING_FIRST(&timer_ring);
-                if (te->when > now) {
-                    timeout_interval = te->when - now;
-                }
-                else {
-                    timeout_interval = 1;
-                }
+        apr_thread_mutex_lock(g_timer_ring_mtx);
+        if (!APR_RING_EMPTY(&timer_ring, timer_event_t, link)) {
+            te = APR_RING_FIRST(&timer_ring);
+            if (te->when > now) {
+                timeout_interval = te->when - now;
             }
             else {
-                timeout_interval = apr_time_from_msec(100);
+                timeout_interval = 1;
             }
-            apr_thread_mutex_unlock(g_timer_ring_mtx);
         }
-
-#if HAVE_SERF
-        rc = serf_context_prerun(g_serf);
-        if (rc != APR_SUCCESS) {
-            /* TOOD: what should do here? ugh. */
+        else {
+            timeout_interval = apr_time_from_msec(100);
         }
-        
-#endif
-        rc = apr_pollset_poll(event_pollset, timeout_interval, &num,
-                              &out_pfd);
+        apr_thread_mutex_unlock(g_timer_ring_mtx);
 
+        rc = apr_pollset_poll(event_pollset, timeout_interval, &num, &out_pfd);
         if (rc != APR_SUCCESS) {
             if (APR_STATUS_IS_EINTR(rc)) {
                 continue;
             }
             if (!APR_STATUS_IS_TIMEUP(rc)) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
+                ap_log_error(APLOG_MARK, APLOG_CRIT, rc, ap_server_conf,
                              "apr_pollset_poll failed.  Attempting to "
                              "shutdown process gracefully");
                 signal_threads(ST_GRACEFUL);
             }
         }
 
-        if (listener_may_exit)
-            break;
+        if (listener_may_exit) {
+            close_listeners(process_slot, &closed);
+            if (terminate_mode == ST_UNGRACEFUL
+                || apr_atomic_read32(&connection_count) == 0)
+                break;
+        }
 
+        now = apr_time_now();
+        apr_thread_mutex_lock(g_timer_ring_mtx);
+        for (ep = APR_RING_FIRST(&timer_ring);
+             ep != APR_RING_SENTINEL(&timer_ring,
+                                     timer_event_t, link);
+             ep = APR_RING_FIRST(&timer_ring))
         {
-            apr_time_t now = apr_time_now();
-            apr_thread_mutex_lock(g_timer_ring_mtx);
-            for (ep = APR_RING_FIRST(&timer_ring);
-                 ep != APR_RING_SENTINEL(&timer_ring,
-                                         timer_event_t, link);
-                 ep = APR_RING_FIRST(&timer_ring))
-            {
-                if (ep->when < now + EVENT_FUDGE_FACTOR) {
-                    APR_RING_REMOVE(ep, link);
-                    push_timer2worker(ep);
-                }
-                else {
-                    break;
-                }
+            if (ep->when < now + EVENT_FUDGE_FACTOR) {
+                APR_RING_REMOVE(ep, link);
+                push_timer2worker(ep);
+            }
+            else {
+                break;
             }
-            apr_thread_mutex_unlock(g_timer_ring_mtx);
         }
+        apr_thread_mutex_unlock(g_timer_ring_mtx);
 
-        while (num && get_worker(&have_idle_worker)) {
+        while (num) {
             pt = (listener_poll_type *) out_pfd->client_data;
             if (pt->type == PT_CSD) {
                 /* one of the sockets is readable */
-                cs = (conn_state_t *) pt->baton;
-                switch (cs->state) {
+                struct timeout_queue *remove_from_q = &write_completion_q;
+                int blocking = 1;
+                cs = (event_conn_state_t *) pt->baton;
+                switch (cs->pub.state) {
                 case CONN_STATE_CHECK_REQUEST_LINE_READABLE:
-                    cs->state = CONN_STATE_READ_REQUEST_LINE;
-                    break;
+                    cs->pub.state = CONN_STATE_READ_REQUEST_LINE;
+                    remove_from_q = &keepalive_q;
+                    /* don't wait for a worker for a keepalive request */
+                    blocking = 0;
+                    /* FALL THROUGH */
                 case CONN_STATE_WRITE_COMPLETION:
+                    get_worker(&have_idle_worker, blocking,
+                               &workers_were_busy);
+                    apr_thread_mutex_lock(timeout_mutex);
+                    TO_QUEUE_REMOVE(*remove_from_q, cs);
+                    rc = apr_pollset_remove(event_pollset, &cs->pfd);
+
+                    /*
+                     * Some of the pollset backends, like KQueue or Epoll
+                     * automagically remove the FD if the socket is closed,
+                     * therefore, we can accept _SUCCESS or _NOTFOUND,
+                     * and we still want to keep going
+                     */
+                    if (rc != APR_SUCCESS && !APR_STATUS_IS_NOTFOUND(rc)) {
+                        ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
+                                     "pollset remove failed");
+                        apr_thread_mutex_unlock(timeout_mutex);
+                        start_lingering_close(cs);
+                        break;
+                    }
+
+                    apr_thread_mutex_unlock(timeout_mutex);
+                    TO_QUEUE_ELEM_INIT(cs);
+                    /* If we didn't get a worker immediately for a keep-alive
+                     * request, we close the connection, so that the client can
+                     * re-connect to a different process.
+                     */
+                    if (!have_idle_worker) {
+                        start_lingering_close(cs);
+                        break;
+                    }
+                    rc = push2worker(out_pfd, event_pollset);
+                    if (rc != APR_SUCCESS) {
+                        ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
+                                     ap_server_conf, "push2worker failed");
+                    }
+                    else {
+                        have_idle_worker = 0;
+                    }
+                    break;
+                case CONN_STATE_LINGER_NORMAL:
+                case CONN_STATE_LINGER_SHORT:
+                    process_lingering_close(cs, out_pfd);
                     break;
                 default:
-                    ap_log_error(APLOG_MARK, APLOG_ERR, rc,
+                    ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                  ap_server_conf,
                                  "event_loop: unexpected state %d",
-                                 cs->state);
-                    AP_DEBUG_ASSERT(0);
-                }
-
-                apr_thread_mutex_lock(timeout_mutex);
-                APR_RING_REMOVE(cs, timeout_list);
-                apr_thread_mutex_unlock(timeout_mutex);
-                APR_RING_ELEM_INIT(cs, timeout_list);
-
-                rc = push2worker(out_pfd, event_pollset);
-                if (rc != APR_SUCCESS) {
-                    ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
-                                 ap_server_conf, "push2worker failed");
-                }
-                else {
-                    have_idle_worker = 0;
+                                 cs->pub.state);
+                    ap_assert(0);
                 }
             }
             else if (pt->type == PT_ACCEPT) {
                 /* A Listener Socket is ready for an accept() */
+                if (workers_were_busy) {
+                    if (!listeners_disabled)
+                        disable_listensocks(process_slot);
+                    listeners_disabled = 1;
+                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
+                                 "All workers busy, not accepting new conns"
+                                 "in this process");
+                }
+                else if (apr_atomic_read32(&connection_count) > threads_per_child
+                         + ap_queue_info_get_idlers(worker_queue_info) *
+                           worker_factor / WORKER_FACTOR_SCALE)
+                {
+                    if (!listeners_disabled)
+                        disable_listensocks(process_slot);
+                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
+                                 "Too many open connections (%u), "
+                                 "not accepting new conns in this process",
+                                 apr_atomic_read32(&connection_count));
+                    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, ap_server_conf,
+                                 "Idle workers: %u",
+                                 ap_queue_info_get_idlers(worker_queue_info));
+                    listeners_disabled = 1;
+                }
+                else if (listeners_disabled) {
+                    listeners_disabled = 0;
+                    enable_listensocks(process_slot);
+                }
+                if (!listeners_disabled) {
+                    lr = (ap_listen_rec *) pt->baton;
+                    ap_pop_pool(&ptrans, worker_queue_info);
 
-                lr = (ap_listen_rec *) pt->baton;
-
-                ap_pop_pool(&ptrans, worker_queue_info);
-
-                if (ptrans == NULL) {
-                    /* create a new transaction pool for each accepted socket */
-                    apr_allocator_t *allocator;
-
-                    apr_allocator_create(&allocator);
-                    apr_allocator_max_free_set(allocator,
-                                               ap_max_mem_free);
-                    apr_pool_create_ex(&ptrans, pconf, NULL, allocator);
-                    apr_allocator_owner_set(allocator, ptrans);
                     if (ptrans == NULL) {
-                        ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
-                                     ap_server_conf,
-                                     "Failed to create transaction pool");
-                        signal_threads(ST_GRACEFUL);
-                        return NULL;
+                        /* create a new transaction pool for each accepted socket */
+                        apr_allocator_t *allocator;
+
+                        apr_allocator_create(&allocator);
+                        apr_allocator_max_free_set(allocator,
+                                                   ap_max_mem_free);
+                        apr_pool_create_ex(&ptrans, pconf, NULL, allocator);
+                        apr_allocator_owner_set(allocator, ptrans);
+                        if (ptrans == NULL) {
+                            ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
+                                         ap_server_conf,
+                                         "Failed to create transaction pool");
+                            signal_threads(ST_GRACEFUL);
+                            return NULL;
+                        }
                     }
-                }
-                apr_pool_tag(ptrans, "transaction");
+                    apr_pool_tag(ptrans, "transaction");
 
-                rc = lr->accept_func(&csd, lr, ptrans);
+                    get_worker(&have_idle_worker, 1, &workers_were_busy);
+                    rc = lr->accept_func(&csd, lr, ptrans);
 
-                /* later we trash rv and rely on csd to indicate
-                 * success/failure
-                 */
-                AP_DEBUG_ASSERT(rc == APR_SUCCESS || !csd);
+                    /* later we trash rv and rely on csd to indicate
+                     * success/failure
+                     */
+                    AP_DEBUG_ASSERT(rc == APR_SUCCESS || !csd);
 
-                if (rc == APR_EGENERAL) {
-                    /* E[NM]FILE, ENOMEM, etc */
-                    resource_shortage = 1;
-                    signal_threads(ST_GRACEFUL);
-                }
+                    if (rc == APR_EGENERAL) {
+                        /* E[NM]FILE, ENOMEM, etc */
+                        resource_shortage = 1;
+                        signal_threads(ST_GRACEFUL);
+                    }
 
-                if (csd != NULL) {
-                    rc = ap_queue_push(worker_queue, csd, NULL, ptrans);
-                    if (rc != APR_SUCCESS) {
-                        /* trash the connection; we couldn't queue the connected
-                         * socket to a worker
-                         */
-                        apr_socket_close(csd);
-                        ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
-                                     ap_server_conf,
-                                     "ap_queue_push failed");
-                        apr_pool_clear(ptrans);
-                        ap_push_pool(worker_queue_info, ptrans);
+                    if (csd != NULL) {
+                        rc = ap_queue_push(worker_queue, csd, NULL, ptrans);
+                        if (rc != APR_SUCCESS) {
+                            /* trash the connection; we couldn't queue the connected
+                             * socket to a worker
+                             */
+                            apr_socket_close(csd);
+                            ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
+                                         ap_server_conf,
+                                         "ap_queue_push failed");
+                            apr_pool_clear(ptrans);
+                            ap_push_pool(worker_queue_info, ptrans);
+                        }
+                        else {
+                            have_idle_worker = 0;
+                        }
                     }
                     else {
-                        have_idle_worker = 0;
+                        apr_pool_clear(ptrans);
+                        ap_push_pool(worker_queue_info, ptrans);
                     }
                 }
-                else {
-                    apr_pool_clear(ptrans);
-                    ap_push_pool(worker_queue_info, ptrans);
-                }
             }               /* if:else on pt->type */
-#if HAVE_SERF
-            else if (pt->type == PT_SERF) {
-                /* send socket to serf. */
-                /* XXXX: this doesn't require get_worker(&have_idle_worker) */
-                serf_event_trigger(g_serf, pt->baton, out_pfd);
-            }
-#endif
             out_pfd++;
             num--;
         }                   /* while for processing poll */
 
         /* XXX possible optimization: stash the current time for use as
          * r->request_time for new requests
          */
-        time_now = apr_time_now();
-
-        /* handle timed out sockets */
-        apr_thread_mutex_lock(timeout_mutex);
-
-        /* Step 1: keepalive timeouts */
-        cs = APR_RING_FIRST(&keepalive_timeout_head);
-        timeout_time = time_now + TIMEOUT_FUDGE_FACTOR;
-        while (!APR_RING_EMPTY(&keepalive_timeout_head, conn_state_t, timeout_list)
-               && cs->expiration_time < timeout_time) {
+        now = apr_time_now();
+        /* we only do this once per 0.1s (TIMEOUT_FUDGE_FACTOR) */
+        if (now > timeout_time) {
+            struct process_score *ps;
+            timeout_time = now + TIMEOUT_FUDGE_FACTOR;
 
-            cs->state = CONN_STATE_LINGER;
-
-            APR_RING_REMOVE(cs, timeout_list);
-            apr_thread_mutex_unlock(timeout_mutex);
+            /* handle timed out sockets */
+            apr_thread_mutex_lock(timeout_mutex);
 
-            if (!get_worker(&have_idle_worker)) {
-                apr_thread_mutex_lock(timeout_mutex);
-                APR_RING_INSERT_HEAD(&keepalive_timeout_head, cs,
-                                     conn_state_t, timeout_list);
-                break;
+            /* Step 1: keepalive timeouts */
+            /* If all workers are busy, we kill older keep-alive connections so that they
+             * may connect to another process.
+             */
+            if (workers_were_busy && keepalive_q.count) {
+                ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, ap_server_conf,
+                             "All workers are busy, will close %d keep-alive "
+                             "connections",
+                             keepalive_q.count);
+                process_timeout_queue(&keepalive_q,
+                                      timeout_time + ap_server_conf->keep_alive_timeout,
+                                      start_lingering_close);
             }
-
-            rc = push2worker(&cs->pfd, event_pollset);
-
-            if (rc != APR_SUCCESS) {
-                return NULL;
-                /* XXX return NULL looks wrong - not an init failure
-                 * that bypasses all the cleanup outside the main loop
-                 * break seems more like it
-                 * need to evaluate seriousness of push2worker failures
-                 */
+            else {
+                process_timeout_queue(&keepalive_q, timeout_time,
+                                      start_lingering_close);
             }
-            have_idle_worker = 0;
-            apr_thread_mutex_lock(timeout_mutex);
-            cs = APR_RING_FIRST(&keepalive_timeout_head);
-        }
-
-        /* Step 2: write completion timeouts */
-        cs = APR_RING_FIRST(&timeout_head);
-        while (!APR_RING_EMPTY(&timeout_head, conn_state_t, timeout_list)
-               && cs->expiration_time < timeout_time) {
-
-            cs->state = CONN_STATE_LINGER;
-            APR_RING_REMOVE(cs, timeout_list);
+            /* Step 2: write completion timeouts */
+            process_timeout_queue(&write_completion_q, timeout_time, start_lingering_close);
+            /* Step 3: (normal) lingering close completion timeouts */
+            process_timeout_queue(&linger_q, timeout_time, stop_lingering_close);
+            /* Step 4: (short) lingering close completion timeouts */
+            process_timeout_queue(&short_linger_q, timeout_time, stop_lingering_close);
+
+            ps = ap_get_scoreboard_process(process_slot);
+            ps->write_completion = write_completion_q.count;
+            ps->lingering_close = linger_q.count + short_linger_q.count;
+            ps->keep_alive = keepalive_q.count;
             apr_thread_mutex_unlock(timeout_mutex);
 
-            if (!get_worker(&have_idle_worker)) {
-                apr_thread_mutex_lock(timeout_mutex);
-                APR_RING_INSERT_HEAD(&timeout_head, cs,
-                                     conn_state_t, timeout_list);
-                break;
-            }
-
-            rc = push2worker(&cs->pfd, event_pollset);
-            if (rc != APR_SUCCESS) {
-                return NULL;
-            }
-            have_idle_worker = 0;
-            apr_thread_mutex_lock(timeout_mutex);
-            cs = APR_RING_FIRST(&timeout_head);
+            ps->connections = apr_atomic_read32(&connection_count);
+            /* XXX: should count CONN_STATE_SUSPENDED and set ps->suspended */
         }
-
-        apr_thread_mutex_unlock(timeout_mutex);
-
+        if (listeners_disabled && !workers_were_busy &&
+            (int)apr_atomic_read32(&connection_count) <
+            ((int)ap_queue_info_get_idlers(worker_queue_info) - 1) *
+            worker_factor / WORKER_FACTOR_SCALE + threads_per_child)
+        {
+            listeners_disabled = 0;
+            enable_listensocks(process_slot);
+        }
+        /*
+         * XXX: do we need to set some timeout that re-enables the listensocks
+         * XXX: in case no other event occurs?
+         */
     }     /* listener main loop */
 
-    ap_close_listeners();
+    close_listeners(process_slot, &closed);
     ap_queue_term(worker_queue);
-    dying = 1;
-    ap_scoreboard_image->parent[process_slot].quiescing = 1;
-
-    /* wake up the main thread */
-    kill(ap_my_pid, SIGTERM);
 
     apr_thread_exit(thd, APR_SUCCESS);
     return NULL;
 }
 
 /* XXX For ungraceful termination/restart, we definitely don't want to

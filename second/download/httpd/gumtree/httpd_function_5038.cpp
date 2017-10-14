static void * APR_THREAD_FUNC listener_thread(apr_thread_t * thd, void *dummy)
{
    timer_event_t *ep;
    timer_event_t *te;
    apr_status_t rc;
    proc_info *ti = dummy;
    int process_slot = ti->pid;
    apr_pool_t *tpool = apr_thread_pool_get(thd);
    void *csd = NULL;
    apr_pool_t *ptrans;         /* Pool for per-transaction stuff */
    ap_listen_rec *lr;
    int have_idle_worker = 0;
    conn_state_t *cs;
    const apr_pollfd_t *out_pfd;
    apr_int32_t num = 0;
    apr_time_t time_now = 0;
    apr_interval_time_t timeout_interval;
    apr_time_t timeout_time;
    listener_poll_type *pt;

    free(ti);

    /* the following times out events that are really close in the future
     *   to prevent extra poll calls
     *
     * current value is .1 second
     */
#define TIMEOUT_FUDGE_FACTOR 100000
#define EVENT_FUDGE_FACTOR 10000

    rc = init_pollset(tpool);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                     "failed to initialize pollset, "
                     "attempting to shutdown process gracefully");
        signal_threads(ST_GRACEFUL);
        return NULL;
    }

    /* Unblock the signal used to wake this thread up, and set a handler for
     * it.
     */
    unblock_signal(LISTENER_SIGNAL);
    apr_signal(LISTENER_SIGNAL, dummy_signal_handler);

    while (!listener_may_exit) {

        if (requests_this_child <= 0) {
            check_infinite_requests();
        }


        {
            apr_time_t now = apr_time_now();
            apr_thread_mutex_lock(g_timer_ring_mtx);

            if (!APR_RING_EMPTY(&timer_ring, timer_event_t, link)) {
                te = APR_RING_FIRST(&timer_ring);
                if (te->when > now) {
                    timeout_interval = te->when - now;
                }
                else {
                    timeout_interval = 1;
                }
            }
            else {
                timeout_interval = apr_time_from_msec(100);
            }
            apr_thread_mutex_unlock(g_timer_ring_mtx);
        }

#if HAVE_SERF
        rc = serf_context_prerun(g_serf);
        if (rc != APR_SUCCESS) {
            /* TOOD: what should do here? ugh. */
        }
        
#endif
        rc = apr_pollset_poll(event_pollset, timeout_interval, &num,
                              &out_pfd);

        if (rc != APR_SUCCESS) {
            if (APR_STATUS_IS_EINTR(rc)) {
                continue;
            }
            if (!APR_STATUS_IS_TIMEUP(rc)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                             "apr_pollset_poll failed.  Attempting to "
                             "shutdown process gracefully");
                signal_threads(ST_GRACEFUL);
            }
        }

        if (listener_may_exit)
            break;

        {
            apr_time_t now = apr_time_now();
            apr_thread_mutex_lock(g_timer_ring_mtx);
            for (ep = APR_RING_FIRST(&timer_ring);
                 ep != APR_RING_SENTINEL(&timer_ring,
                                         timer_event_t, link);
                 ep = APR_RING_FIRST(&timer_ring))
            {
                if (ep->when < now + EVENT_FUDGE_FACTOR) {
                    APR_RING_REMOVE(ep, link);
                    push_timer2worker(ep);
                }
                else {
                    break;
                }
            }
            apr_thread_mutex_unlock(g_timer_ring_mtx);
        }

        while (num && get_worker(&have_idle_worker)) {
            pt = (listener_poll_type *) out_pfd->client_data;
            if (pt->type == PT_CSD) {
                /* one of the sockets is readable */
                cs = (conn_state_t *) pt->baton;
                switch (cs->state) {
                case CONN_STATE_CHECK_REQUEST_LINE_READABLE:
                    cs->state = CONN_STATE_READ_REQUEST_LINE;
                    break;
                case CONN_STATE_WRITE_COMPLETION:
                    break;
                default:
                    ap_log_error(APLOG_MARK, APLOG_ERR, rc,
                                 ap_server_conf,
                                 "event_loop: unexpected state %d",
                                 cs->state);
                    AP_DEBUG_ASSERT(0);
                }

                apr_thread_mutex_lock(timeout_mutex);
                APR_RING_REMOVE(cs, timeout_list);
                apr_thread_mutex_unlock(timeout_mutex);
                APR_RING_ELEM_INIT(cs, timeout_list);

                rc = push2worker(out_pfd, event_pollset);
                if (rc != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                 ap_server_conf, "push2worker failed");
                }
                else {
                    have_idle_worker = 0;
                }
            }
            else if (pt->type == PT_ACCEPT) {
                /* A Listener Socket is ready for an accept() */

                lr = (ap_listen_rec *) pt->baton;

                ap_pop_pool(&ptrans, worker_queue_info);

                if (ptrans == NULL) {
                    /* create a new transaction pool for each accepted socket */
                    apr_allocator_t *allocator;

                    apr_allocator_create(&allocator);
                    apr_allocator_max_free_set(allocator,
                                               ap_max_mem_free);
                    apr_pool_create_ex(&ptrans, pconf, NULL, allocator);
                    apr_allocator_owner_set(allocator, ptrans);
                    if (ptrans == NULL) {
                        ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                     ap_server_conf,
                                     "Failed to create transaction pool");
                        signal_threads(ST_GRACEFUL);
                        return NULL;
                    }
                }
                apr_pool_tag(ptrans, "transaction");

                rc = lr->accept_func(&csd, lr, ptrans);

                /* later we trash rv and rely on csd to indicate
                 * success/failure
                 */
                AP_DEBUG_ASSERT(rc == APR_SUCCESS || !csd);

                if (rc == APR_EGENERAL) {
                    /* E[NM]FILE, ENOMEM, etc */
                    resource_shortage = 1;
                    signal_threads(ST_GRACEFUL);
                }

                if (csd != NULL) {
                    rc = ap_queue_push(worker_queue, csd, NULL, ptrans);
                    if (rc != APR_SUCCESS) {
                        /* trash the connection; we couldn't queue the connected
                         * socket to a worker
                         */
                        apr_socket_close(csd);
                        ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                     ap_server_conf,
                                     "ap_queue_push failed");
                        apr_pool_clear(ptrans);
                        ap_push_pool(worker_queue_info, ptrans);
                    }
                    else {
                        have_idle_worker = 0;
                    }
                }
                else {
                    apr_pool_clear(ptrans);
                    ap_push_pool(worker_queue_info, ptrans);
                }
            }               /* if:else on pt->type */
#if HAVE_SERF
            else if (pt->type == PT_SERF) {
                /* send socket to serf. */
                /* XXXX: this doesn't require get_worker(&have_idle_worker) */
                serf_event_trigger(g_serf, pt->baton, out_pfd);
            }
#endif
            out_pfd++;
            num--;
        }                   /* while for processing poll */

        /* XXX possible optimization: stash the current time for use as
         * r->request_time for new requests
         */
        time_now = apr_time_now();

        /* handle timed out sockets */
        apr_thread_mutex_lock(timeout_mutex);

        /* Step 1: keepalive timeouts */
        cs = APR_RING_FIRST(&keepalive_timeout_head);
        timeout_time = time_now + TIMEOUT_FUDGE_FACTOR;
        while (!APR_RING_EMPTY(&keepalive_timeout_head, conn_state_t, timeout_list)
               && cs->expiration_time < timeout_time) {

            cs->state = CONN_STATE_LINGER;

            APR_RING_REMOVE(cs, timeout_list);
            apr_thread_mutex_unlock(timeout_mutex);

            if (!get_worker(&have_idle_worker)) {
                apr_thread_mutex_lock(timeout_mutex);
                APR_RING_INSERT_HEAD(&keepalive_timeout_head, cs,
                                     conn_state_t, timeout_list);
                break;
            }

            rc = push2worker(&cs->pfd, event_pollset);

            if (rc != APR_SUCCESS) {
                return NULL;
                /* XXX return NULL looks wrong - not an init failure
                 * that bypasses all the cleanup outside the main loop
                 * break seems more like it
                 * need to evaluate seriousness of push2worker failures
                 */
            }
            have_idle_worker = 0;
            apr_thread_mutex_lock(timeout_mutex);
            cs = APR_RING_FIRST(&keepalive_timeout_head);
        }

        /* Step 2: write completion timeouts */
        cs = APR_RING_FIRST(&timeout_head);
        while (!APR_RING_EMPTY(&timeout_head, conn_state_t, timeout_list)
               && cs->expiration_time < timeout_time) {

            cs->state = CONN_STATE_LINGER;
            APR_RING_REMOVE(cs, timeout_list);
            apr_thread_mutex_unlock(timeout_mutex);

            if (!get_worker(&have_idle_worker)) {
                apr_thread_mutex_lock(timeout_mutex);
                APR_RING_INSERT_HEAD(&timeout_head, cs,
                                     conn_state_t, timeout_list);
                break;
            }

            rc = push2worker(&cs->pfd, event_pollset);
            if (rc != APR_SUCCESS) {
                return NULL;
            }
            have_idle_worker = 0;
            apr_thread_mutex_lock(timeout_mutex);
            cs = APR_RING_FIRST(&timeout_head);
        }

        apr_thread_mutex_unlock(timeout_mutex);

    }     /* listener main loop */

    ap_close_listeners();
    ap_queue_term(worker_queue);
    dying = 1;
    ap_scoreboard_image->parent[process_slot].quiescing = 1;

    /* wake up the main thread */
    kill(ap_my_pid, SIGTERM);

    apr_thread_exit(thd, APR_SUCCESS);
    return NULL;
}
static void *APR_THREAD_FUNC worker_thread(apr_thread_t * thd, void *dummy)
{
    proc_info *ti = dummy;
    int process_slot = ti->pid;
    int thread_slot = ti->tid;
    apr_socket_t *csd = NULL;
    event_conn_state_t *cs;
    apr_pool_t *ptrans;         /* Pool for per-transaction stuff */
    apr_status_t rv;
    int is_idle = 0;
    timer_event_t *te = NULL;

    free(ti);

    ap_scoreboard_image->servers[process_slot][thread_slot].pid = ap_my_pid;
    ap_scoreboard_image->servers[process_slot][thread_slot].tid = apr_os_thread_current();
    ap_scoreboard_image->servers[process_slot][thread_slot].generation = retained->my_generation;
    ap_update_child_status_from_indexes(process_slot, thread_slot,
                                        SERVER_STARTING, NULL);

    while (!workers_may_exit) {
        if (!is_idle) {
            rv = ap_queue_info_set_idle(worker_queue_info, NULL);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "ap_queue_info_set_idle failed. Attempting to "
                             "shutdown process gracefully.");
                signal_threads(ST_GRACEFUL);
                break;
            }
            is_idle = 1;
        }

        ap_update_child_status_from_indexes(process_slot, thread_slot,
                                            dying ? SERVER_GRACEFUL : SERVER_READY, NULL);
      worker_pop:
        if (workers_may_exit) {
            break;
        }

        te = NULL;
        rv = ap_queue_pop_something(worker_queue, &csd, &cs, &ptrans, &te);

        if (rv != APR_SUCCESS) {
            /* We get APR_EOF during a graceful shutdown once all the
             * connections accepted by this server process have been handled.
             */
            if (APR_STATUS_IS_EOF(rv)) {
                break;
            }
            /* We get APR_EINTR whenever ap_queue_pop() has been interrupted
             * from an explicit call to ap_queue_interrupt_all(). This allows
             * us to unblock threads stuck in ap_queue_pop() when a shutdown
             * is pending.
             *
             * If workers_may_exit is set and this is ungraceful termination/
             * restart, we are bound to get an error on some systems (e.g.,
             * AIX, which sanity-checks mutex operations) since the queue
             * may have already been cleaned up.  Don't log the "error" if
             * workers_may_exit is set.
             */
            else if (APR_STATUS_IS_EINTR(rv)) {
                goto worker_pop;
            }
            /* We got some other error. */
            else if (!workers_may_exit) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                             "ap_queue_pop failed");
            }
            continue;
        }
        if (te != NULL) {
            te->cbfunc(te->baton);

            {
                apr_thread_mutex_lock(g_timer_skiplist_mtx);
                APR_RING_INSERT_TAIL(&timer_free_ring, te, timer_event_t, link);
                apr_thread_mutex_unlock(g_timer_skiplist_mtx);
            }
        }
        else {
            is_idle = 0;
            worker_sockets[thread_slot] = csd;
            process_socket(thd, ptrans, csd, cs, process_slot, thread_slot);
            worker_sockets[thread_slot] = NULL;
        }
    }

    ap_update_child_status_from_indexes(process_slot, thread_slot,
                                        dying ? SERVER_DEAD :
                                        SERVER_GRACEFUL,
                                        (request_rec *) NULL);

    apr_thread_exit(thd, APR_SUCCESS);
    return NULL;
}
static void * APR_THREAD_FUNC worker_thread(apr_thread_t *thd, void * dummy)
{
    proc_info * ti = dummy;
    int process_slot = ti->pid;
    int thread_slot = ti->tid;
    apr_socket_t *csd = NULL;
    apr_bucket_alloc_t *bucket_alloc;
    apr_pool_t *last_ptrans = NULL;
    apr_pool_t *ptrans;                /* Pool for per-transaction stuff */
    apr_status_t rv;
    int is_idle = 0;

    free(ti);

    ap_scoreboard_image->servers[process_slot][thread_slot].pid = ap_my_pid;
    ap_scoreboard_image->servers[process_slot][thread_slot].tid = apr_os_thread_current();
    ap_scoreboard_image->servers[process_slot][thread_slot].generation = retained->my_generation;
    ap_update_child_status_from_indexes(process_slot, thread_slot, SERVER_STARTING, NULL);

#ifdef HAVE_PTHREAD_KILL
    unblock_signal(WORKER_SIGNAL);
    apr_signal(WORKER_SIGNAL, dummy_signal_handler);
#endif

    while (!workers_may_exit) {
        if (!is_idle) {
            rv = ap_queue_info_set_idle(worker_queue_info, last_ptrans);
            last_ptrans = NULL;
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "ap_queue_info_set_idle failed. Attempting to "
                             "shutdown process gracefully.");
                signal_threads(ST_GRACEFUL);
                break;
            }
            is_idle = 1;
        }

        ap_update_child_status_from_indexes(process_slot, thread_slot, SERVER_READY, NULL);
worker_pop:
        if (workers_may_exit) {
            break;
        }
        rv = ap_queue_pop(worker_queue, &csd, &ptrans);

        if (rv != APR_SUCCESS) {
            /* We get APR_EOF during a graceful shutdown once all the connections
             * accepted by this server process have been handled.
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
        is_idle = 0;
        worker_sockets[thread_slot] = csd;
        bucket_alloc = apr_bucket_alloc_create(ptrans);
        process_socket(thd, ptrans, csd, process_slot, thread_slot, bucket_alloc);
        worker_sockets[thread_slot] = NULL;
        requests_this_child--;
        apr_pool_clear(ptrans);
        last_ptrans = ptrans;
    }

    ap_update_child_status_from_indexes(process_slot, thread_slot,
        (dying) ? SERVER_DEAD : SERVER_GRACEFUL, (request_rec *) NULL);

    apr_thread_exit(thd, APR_SUCCESS);
    return NULL;
}
        /* TODO: requests_this_child should be synchronized - aaron */
        if (requests_this_child <= 0) {
            check_infinite_requests();
        }
        if (listener_may_exit) break;

        if (!have_idle_worker) {
            rv = ap_queue_info_wait_for_idler(worker_queue_info,
                                              &recycled_pool);
            if (APR_STATUS_IS_EOF(rv)) {
                break; /* we've been signaled to die now */
            }
            else if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "apr_queue_info_wait failed. Attempting to "
                             " shutdown process gracefully.");
                signal_threads(ST_GRACEFUL);
                break;
            }
            have_idle_worker = 1;
        }
            
        /* We've already decremented the idle worker count inside
         * ap_queue_info_wait_for_idler. */

        if ((rv = SAFE_ACCEPT(apr_proc_mutex_lock(accept_mutex)))
            != APR_SUCCESS) {
            int level = APLOG_EMERG;

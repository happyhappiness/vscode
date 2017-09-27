
        /* We've already decremented the idle worker count inside
         * ap_queue_info_wait_for_idler. */

        if ((rv = SAFE_ACCEPT(apr_proc_mutex_lock(accept_mutex)))
            != APR_SUCCESS) {
            int level = APLOG_EMERG;

            if (listener_may_exit) {
                break;
            }
            if (ap_scoreboard_image->parent[process_slot].generation !=
                ap_scoreboard_image->global->running_generation) {
                level = APLOG_DEBUG; /* common to get these at restart time */
            }
            ap_log_error(APLOG_MARK, level, rv, ap_server_conf,
                         "apr_proc_mutex_lock failed. Attempting to shutdown "
                         "process gracefully.");
            signal_threads(ST_GRACEFUL);
            break;                    /* skip the lock release */
        }

        if (!ap_listeners->next) {
            /* Only one listener, so skip the poll */
            lr = ap_listeners;

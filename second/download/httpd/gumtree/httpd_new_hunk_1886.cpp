
        /* We've already decremented the idle worker count inside
         * ap_queue_info_wait_for_idler. */

        if ((rv = SAFE_ACCEPT(apr_proc_mutex_lock(accept_mutex)))
            != APR_SUCCESS) {

            if (!listener_may_exit) {
                accept_mutex_error("lock", rv, process_slot);
            }
            break;                    /* skip the lock release */
        }

        if (!ap_listeners->next) {
            /* Only one listener, so skip the poll */
            lr = ap_listeners;

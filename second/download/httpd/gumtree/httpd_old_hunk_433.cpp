                worker_stack_awaken_next(idle_worker_stack);
                process_socket(ptrans, csd, process_slot,
                               thread_slot, bucket_alloc);
                apr_pool_clear(ptrans);
                requests_this_child--;
            }
        }
        else {
            if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(accept_mutex)))
                != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "apr_proc_mutex_unlock failed. Attempting to "

                worker_stack_awaken_next(idle_worker_stack);
                process_socket(ptrans, csd, process_slot,
                               thread_slot, bucket_alloc);
                apr_pool_clear(ptrans);
                requests_this_child--;
            }
            if ((ap_mpm_pod_check(pod) == APR_SUCCESS) ||
                (ap_my_generation !=
                 ap_scoreboard_image->global->running_generation)) {
                signal_threads(ST_GRACEFUL);
                break;
            }
        }
        else {
            if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(accept_mutex)))
                != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "apr_proc_mutex_unlock failed. Attempting to "

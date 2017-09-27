        }
        else {
            if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(accept_mutex)))
                != APR_SUCCESS) {
                int level = APLOG_EMERG;

                if (ap_scoreboard_image->parent[process_slot].generation != 
                    ap_scoreboard_image->global->running_generation) {
                    level = APLOG_DEBUG; /* common to get these at restart time */
                }
                ap_log_error(APLOG_MARK, level, rv, ap_server_conf,
                             "apr_proc_mutex_unlock failed. Attempting to "
                             "shutdown process gracefully.");
                signal_threads(ST_GRACEFUL);
            }
            break;
        }
    }

    ap_queue_term(worker_queue);
    dying = 1;
    ap_scoreboard_image->parent[process_slot].quiescing = 1;

    /* wake up the main thread */
    kill(ap_my_pid, SIGTERM);

        }
        /* Start the listener only when there are workers available */
        if (!listener_started && threads_created) {
            create_listener_thread(ts);
            listener_started = 1;
        }
        if (start_thread_may_exit || threads_created == threads_per_child) {
            break;
        }
        /* wait for previous generation to clean up an entry */
        apr_sleep(apr_time_from_sec(1));
        ++loops;
        if (loops % 120 == 0) { /* every couple of minutes */
            if (prev_threads_created == threads_created) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                             "child %" APR_PID_T_FMT " isn't taking over "
                             "slots very quickly (%d of %d)",
                             ap_my_pid, threads_created, threads_per_child);
            }
            prev_threads_created = threads_created;
        }
    }

    /* What state should this child_main process be listed as in the

        int index;
        apr_time_t cutoff = 0;

        /* Close our listeners, and then ask our children to do same */
        ap_close_listeners();
        ap_worker_pod_killpg(pod, ap_daemons_limit, TRUE);
        ap_relieve_child_processes(worker_note_child_killed);

        if (!child_fatal) {
            /* cleanup pid file on normal shutdown */
            ap_remove_pid(pconf, ap_pid_fname);
            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00296)
                         "caught " AP_SIG_GRACEFUL_STOP_STRING
                         ", shutting down gracefully");
        }

        if (ap_graceful_shutdown_timeout) {
            cutoff = apr_time_now() +

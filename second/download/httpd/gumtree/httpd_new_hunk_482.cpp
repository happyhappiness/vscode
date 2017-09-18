    else {
        /* Parent process */
        char restart;
        is_parent_process = TRUE;

        if (ap_setup_listeners(ap_server_conf) < 1) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, 0, s,
                         "no listening sockets available, shutting down");
            return 1;
        }

        ap_log_pid(pconf, ap_pid_fname);


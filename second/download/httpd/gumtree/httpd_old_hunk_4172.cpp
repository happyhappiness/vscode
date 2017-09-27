    }

    if ((num_listensocks = ap_setup_listeners(ap_server_conf)) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT | level_flags, 0,
                     (startup ? NULL : s),
                     "no listening sockets available, shutting down");
        return DONE;
    }

    if (one_process) {
        num_buckets = 1;
    }
    else if (!retained->is_graceful) { /* Preserve the number of buckets

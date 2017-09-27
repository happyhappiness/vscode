
    /*
     * record that we've entered the world !
     */
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                "%s configured -- resuming normal operations",
                ap_get_server_description());

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
                "Server built: %s", ap_get_server_built());

    restart_pending = shutdown_pending = 0;


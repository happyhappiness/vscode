    }
    else
    {
        /* A real-honest to goodness parent */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     "%s configured -- resuming normal operations",
                     ap_get_server_version());
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     "Server built: %s", ap_get_server_built());

        restart = master_main(ap_server_conf, shutdown_event, restart_event);

        if (!restart)

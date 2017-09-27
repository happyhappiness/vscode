        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00455)
                     "%s configured -- resuming normal operations",
                     ap_get_server_description());
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00456)
                     "Server built: %s", ap_get_server_built());
        ap_log_command_line(plog, s);

        restart = master_main(ap_server_conf, shutdown_event, restart_event);

        if (!restart)
        {
            /* Shutting down. Clean up... */

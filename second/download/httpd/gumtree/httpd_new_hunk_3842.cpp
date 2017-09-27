    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00224)
            "%s configured -- resuming normal operations",
            ap_get_server_description());
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00225)
            "Server built: %s", ap_get_server_built());
    ap_log_command_line(plog, s);
    ap_log_mpm_common(s);
    show_server_data();

    mpm_state = AP_MPMQ_RUNNING;
    while (!restart_pending && !shutdown_pending) {
        perform_idle_server_maintenance(pconf);
        if (show_settings)

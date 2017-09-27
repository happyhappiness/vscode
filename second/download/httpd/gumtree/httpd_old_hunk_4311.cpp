    if (s == NULL) {
        return s;
    }

    init_config_globals(p);

    /* All server-wide config files now have the SAME syntax... */
    error = process_command_config(s, ap_server_pre_read_config, conftree,
                                   p, ptemp);
    if (error) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, 0, NULL, "%s: %s",
                     ap_server_argv0, error);

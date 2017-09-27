    if (error) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, 0, NULL,
                     "%s: %s", ap_server_argv0, error);
        return NULL;
    }

    error = process_command_config(s, ap_server_post_read_config, conftree,
                                   p, ptemp);

    if (error) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, 0, NULL, "%s: %s",
                     ap_server_argv0, error);

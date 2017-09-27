    if (error) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, 0, NULL,
                     "%s: %s", ap_server_argv0, error);
        return NULL;
    }

    error = ap_check_mpm();
    if (error) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, 0, NULL,
                     "%s: Configuration error: %s", ap_server_argv0, error);
        return NULL;
    }

    /*
     * We have loaded the dynamic modules. From now on we know exactly how
     * long the config vectors need to be.
     */
    conf_vector_length = total_modules;
    apr_pool_cleanup_register(p, NULL, reset_conf_vector_length,
                              apr_pool_cleanup_null);

    error = process_command_config(s, ap_server_post_read_config, conftree,
                                   p, ptemp);

    if (error) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, 0, NULL, "%s: %s",
                     ap_server_argv0, error);

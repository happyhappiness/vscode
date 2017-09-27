    void *reported;

    apr_pool_userdata_get(&reported, SUEXEC_POST_CONFIG_USERDATA,
                          s->process->pool);

    if ((reported == NULL) && ap_unixd_config.suexec_enabled) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
                     "suEXEC mechanism enabled (wrapper: %s)", SUEXEC_BIN);

        apr_pool_userdata_set((void *)1, SUEXEC_POST_CONFIG_USERDATA,
                              apr_pool_cleanup_null, s->process->pool);
    }


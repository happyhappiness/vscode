ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, APR_SUCCESS, s,
                     "%s",
                     apr_pstrcat(p, (is_conf
                                     ? "<Directory>, <Location>, or similar"
                                     : format_authz_command(p, section)),
                                 " directive contains only negative "
                                 "authorization directives", NULL));
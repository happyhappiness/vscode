ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00104)
                         "unable to start piped log program '%s': %s",
                         pl->program, apr_strerror(status, buf, sizeof(buf)));
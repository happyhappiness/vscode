ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00103)
                     "piped_log_spawn: unable to setup child process '%s': %s",
                     pl->program, apr_strerror(status, buf, sizeof(buf)));
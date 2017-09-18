ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                         "piped_log_maintenance: unable to respawn '%s': %s",
                         pl->program, apr_strerror(stats, buf, sizeof(buf)));
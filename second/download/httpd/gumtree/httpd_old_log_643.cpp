ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                         "%s: module \"%s\" could not be loaded, because"
                         " the dynamic", ap_server_argv0, m->name);
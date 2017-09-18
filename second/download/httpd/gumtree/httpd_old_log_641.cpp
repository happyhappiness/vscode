ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                     "%s: module \"%s\" is not compatible with this "
                     "version of Apache.", ap_server_argv0, m->name);
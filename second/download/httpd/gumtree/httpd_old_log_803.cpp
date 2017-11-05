ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s: module \"%s\" is not compatible with this "
                     "version of Apache (found %d, need %d).",
                     ap_server_argv0, m->name, m->version,
                     MODULE_MAGIC_NUMBER_MAJOR);
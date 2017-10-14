ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "can't query MPM state; not restarting "
                         "piped log program '%s'",
                         pl->program);
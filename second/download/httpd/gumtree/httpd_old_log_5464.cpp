ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL,
                         "(%d)%s: cannot allocate scoreboard",
                         errno, strerror(errno));
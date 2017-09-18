ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                     "Syntax error in -C/-c directive:" APR_EOL_STR "%s",
                     errmsg);
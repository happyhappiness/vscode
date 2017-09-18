ap_log_error(APLOG_MARK, APLOG_CRIT | APLOG_NOERRNO, 0, NULL,
                 "[%s] file %s, line %d, assertion \"%s\" failed",
                 time_str, szFile, nLine, szExp);
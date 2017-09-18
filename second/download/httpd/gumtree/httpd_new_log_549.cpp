ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot store SSL session to DBM file `%s'",
                     mc->szSessionCacheDataFile);
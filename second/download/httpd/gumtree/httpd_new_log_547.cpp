ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot create SSLSessionCache DBM file `%s'",
                     mc->szSessionCacheDataFile);
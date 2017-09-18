ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot re-open SSLSessionCache DBM file `%s' for "
                         "expiring",
                         mc->szSessionCacheDataFile);
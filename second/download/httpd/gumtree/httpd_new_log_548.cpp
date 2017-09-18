ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot open SSLSessionCache DBM file `%s' for writing "
                     "(store)",
                     mc->szSessionCacheDataFile);
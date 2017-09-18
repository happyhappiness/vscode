ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "Cannot open SSLSessionCache DBM file `%s' for status "
                     "retrival",
                     mc->szSessionCacheDataFile);
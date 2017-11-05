ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                     "Cannot open SSLSessionCache DBM file `%s' for status "
                     "retrival",
                     mc->szSessionCacheDataFile);
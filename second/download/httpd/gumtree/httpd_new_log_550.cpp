ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                     "Cannot open SSLSessionCache DBM file `%s' for reading "
                     "(fetch)",
                     mc->szSessionCacheDataFile);
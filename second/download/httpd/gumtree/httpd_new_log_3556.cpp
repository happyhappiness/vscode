ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00805)
                 "data size too large for DBM socache: %d >= %d",
                 (idlen + nData), PAIRMAX);
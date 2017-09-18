ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "data size too large for DBM session cache: %d >= %d",
                 (idlen + nData), PAIRMAX);
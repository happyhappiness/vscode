ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "streamline session data size too large: %d > %d",
                 nData, sizeof(ucaData));
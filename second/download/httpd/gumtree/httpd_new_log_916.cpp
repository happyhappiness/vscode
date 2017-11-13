ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "streamline session data size too large: %d > "
                     "%" APR_SIZE_T_FMT,
                     nData, sizeof(ucaData));
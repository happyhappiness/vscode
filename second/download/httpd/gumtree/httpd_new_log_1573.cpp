ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Init: Failed to generate temporary "
                     "%d bit EC parameters, only 256 bits supported", bits);
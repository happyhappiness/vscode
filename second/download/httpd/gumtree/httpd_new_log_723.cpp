ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "WARNING: MaxRequestsPerThread was set below 0"
                     "reset to 0, but this may not be what you want.");
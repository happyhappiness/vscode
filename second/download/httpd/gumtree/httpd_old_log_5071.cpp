ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                         "Couldn't create a Thread Safe Pollset. "
                         "Is it supported on your platform?"
                         "Also check system or user limits!");
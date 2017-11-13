ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "Heartmonitor: Failed to register watchdog "
                     "callback (%s)", HM_WATHCHDOG_NAME);
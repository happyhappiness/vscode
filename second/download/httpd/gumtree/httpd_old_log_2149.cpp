ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "%s: Alert: %s:%s:%s",
                     SSL_LIBRARY_NAME, str,
                     SSL_alert_type_string_long(rc),
                     SSL_alert_desc_string_long(rc));
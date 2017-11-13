ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
                      "%s: Alert: %s:%s:%s",
                      MODSSL_LIBRARY_NAME, str,
                      SSL_alert_type_string_long(rc),
                      SSL_alert_desc_string_long(rc));
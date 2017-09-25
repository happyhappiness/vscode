                         "%s: Write: %s",
                         SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
        }
        else if (where & SSL_CB_ALERT) {
            char *str = (where & SSL_CB_READ) ? "read" : "write";
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "%s: Alert: %s:%s:%s\n",
                         SSL_LIBRARY_NAME, str,
                         SSL_alert_type_string_long(rc),
                         SSL_alert_desc_string_long(rc));
        }
        else if (where & SSL_CB_EXIT) {
            if (rc == 0) {

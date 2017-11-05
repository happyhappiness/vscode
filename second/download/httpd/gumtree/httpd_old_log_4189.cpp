ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "CA certificate: %s",
                     X509_NAME_oneline(name, name_buf, sizeof(name_buf)));
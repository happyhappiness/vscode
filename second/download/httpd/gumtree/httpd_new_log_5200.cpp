ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
                      "%s: Write: %s",
                      MODSSL_LIBRARY_NAME, SSL_state_string_long(ssl));
ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "%s: Exit: failed in %s",
                             SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
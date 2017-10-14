ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
                              "Failed to set SNI extension for SSL Proxy "
                              "request to '%s'", hostname_note);
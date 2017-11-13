ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                          "SSL client authentication failed, "
                          "accepting certificate based on "
                          "\"SSLVerifyClient optional_no_ca\" "
                          "configuration");
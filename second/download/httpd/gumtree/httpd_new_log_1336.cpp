ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         c->base_server,
                         "SSL client authentication failed, "
                         "accepting certificate based on "
                         "\"SSLVerifyClient optional_no_ca\" "
                         "configuration");
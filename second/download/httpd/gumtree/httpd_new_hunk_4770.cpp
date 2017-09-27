                ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(01884)
                             "Operating in SSL FIPS mode");
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01885) "FIPS mode failed");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                ssl_die(s);
            }
        }
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(01886)
                     "SSL FIPS mode disabled");

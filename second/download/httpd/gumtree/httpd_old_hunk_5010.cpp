                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                ssl_die(s);
            }
        }
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(01886)
                     "SSL FIPS mode disabled");
    }
#endif

    /*
     * read server private keys/public certs into memory.

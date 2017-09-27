                ssl_log_ssl_error(APLOG_MARK, APLOG_EMERG, s);
                ssl_die();
            }
        }
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
                     "SSL FIPS mode disabled");
    }
#endif

    /*
     * read server private keys/public certs into memory.

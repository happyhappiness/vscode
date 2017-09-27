    ssl_rand_seed(base_server, ptemp, SSL_RSCTX_STARTUP, "Init: ");

#ifdef HAVE_FIPS
    if(sc->fips) {
        if (!FIPS_mode()) {
            if (FIPS_mode_set(1)) {
                ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(01884)
                             "Operating in SSL FIPS mode");
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01885) "FIPS mode failed");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                ssl_die();
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

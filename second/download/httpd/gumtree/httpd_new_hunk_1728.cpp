            if (FIPS_mode_set(1)) {
                ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
                             "Operating in SSL FIPS mode");
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, "FIPS mode failed");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
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
     * decrypting any encrypted keys via configured SSLPassPhraseDialogs
     * anything that needs to live longer than ptemp needs to also survive
     * restarts, in which case they'll live inside s->process->pool.
     */
    ssl_pphrase_Handle(base_server, ptemp);

    if (ssl_tmp_keys_init(base_server)) {
        return !OK;
    }

    /*
     * initialize the mutex handling
     */
    if (!ssl_mutex_init(base_server, p)) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }
#ifdef HAVE_OCSP_STAPLING
    if (!ssl_stapling_mutex_init(base_server, p)) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    ssl_stapling_ex_init();
#endif

    /*
     * initialize session caching
     */
    ssl_scache_init(base_server, p);


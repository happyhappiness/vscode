     * Seed the Pseudo Random Number Generator (PRNG)
     * only need ptemp here; nothing inside allocated from the pool
     * needs to live once we return from ssl_rand_seed().
     */
    ssl_rand_seed(base_server, ptemp, SSL_RSCTX_STARTUP, "Init: ");

#ifdef HAVE_FIPS
    if(sc->fips) {
        if (!FIPS_mode()) {
            if (FIPS_mode_set(1)) {
                ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
                             "Operating in SSL FIPS mode");
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, "FIPS mode failed");
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
     * decrypting any encrypted keys via configured SSLPassPhraseDialogs
     * anything that needs to live longer than ptemp needs to also survive
     * restarts, in which case they'll live inside s->process->pool.
     */

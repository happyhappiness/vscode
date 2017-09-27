    SSL_CTX *ctx = mctx->ssl_ctx;
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->stapling_cache == NULL) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01958)
                     "SSLStapling: no stapling cache available");
        ssl_die();
    }
    if (ssl_stapling_mutex_init(s, ptemp) == FALSE) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01959)
                     "SSLStapling: cannot initialise stapling mutex");
        ssl_die();
    }
    /* Set some default values for parameters if they are not set */
    if (mctx->stapling_resptime_skew == UNSET) {
        mctx->stapling_resptime_skew = 60 * 5;
    }
    if (mctx->stapling_cache_timeout == UNSET) {

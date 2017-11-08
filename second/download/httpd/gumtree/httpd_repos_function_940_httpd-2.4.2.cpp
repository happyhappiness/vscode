void ssl_scache_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;
    struct ap_socache_hints hints;

    /* The very first invocation of this function will be the
     * post_config invocation during server startup; do nothing for
     * this first (and only the first) time through, since the pool
     * will be immediately cleared anyway.  For every subsequent
     * invocation, initialize the configured cache. */
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG)
        return;

#ifdef HAVE_OCSP_STAPLING
    if (mc->stapling_cache) {
        memset(&hints, 0, sizeof hints);
        hints.avg_obj_size = 1500;
        hints.avg_id_len = 20;
        hints.expiry_interval = 300;

        rv = mc->stapling_cache->init(mc->stapling_cache_context,
                                     "mod_ssl-stapling", &hints, s, p);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01872)
                         "Could not initialize stapling cache. Exiting.");
            ssl_die();
        }
    }
#endif

    /*
     * Warn the user that he should use the session cache.
     * But we can operate without it, of course.
     */
    if (mc->sesscache == NULL) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01873)
                     "Init: Session Cache is not configured "
                     "[hint: SSLSessionCache]");
        return;
    }

    memset(&hints, 0, sizeof hints);
    hints.avg_obj_size = 150;
    hints.avg_id_len = 30;
    hints.expiry_interval = 30;

    rv = mc->sesscache->init(mc->sesscache_context, "mod_ssl-session", &hints, s, p);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01874)
                     "Could not initialize session cache. Exiting.");
        ssl_die();
    }
}

        rv = mc->stapling_cache->init(mc->stapling_cache_context,
                                     "mod_ssl-stapling", &hints, s, p);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01872)
                         "Could not initialize stapling cache. Exiting.");
            ssl_die(s);
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
        ssl_die(s);
    }
}

void ssl_scache_kill(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);


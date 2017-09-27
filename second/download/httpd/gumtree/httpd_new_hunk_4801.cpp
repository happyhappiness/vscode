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

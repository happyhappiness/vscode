
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %s [-C \"directive\"] [-c \"directive\"]", pad);

#ifdef WIN32
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %s [-w] [-k start|restart|stop|shutdown]", pad);
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %s [-k install|config|uninstall] [-n service_name]",
                 pad);
#endif
#ifdef AP_MPM_WANT_SIGNAL_SERVER
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,

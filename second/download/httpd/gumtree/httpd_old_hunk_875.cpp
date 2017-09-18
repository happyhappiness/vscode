#ifdef AP_MPM_WANT_SIGNAL_SERVER
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %s [-k start|restart|graceful|stop]",
                 pad);
#endif
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %s [-v] [-V] [-h] [-l] [-L] [-t]", pad);
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "Options:");

#ifdef SHARED_CORE
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -R directory      : specify an alternate location for "

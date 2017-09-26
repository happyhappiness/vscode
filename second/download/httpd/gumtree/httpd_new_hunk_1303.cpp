    return process;
}

static void usage(process_rec *process)
{
    const char *bin = process->argv[0];
    int pad_len = strlen(bin);

#ifdef SHARED_CORE
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL ,
                 "Usage: %s [-R directory] [-D name] [-d directory] [-f file]",
                 bin);
#else
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "Usage: %s [-D name] [-d directory] [-f file]", bin);
#endif

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-C \"directive\"] [-c \"directive\"]", pad_len, " ");

#ifdef WIN32
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-w] [-k start|restart|stop|shutdown]", pad_len, " ");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-k install|config|uninstall] [-n service_name]",
                 pad_len, " ");
#endif
#ifdef AP_MPM_WANT_SIGNAL_SERVER
#ifdef AP_MPM_WANT_SET_GRACEFUL_SHUTDOWN
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-k start|restart|graceful|graceful-stop|stop]",
                 pad_len, " ");
#else
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-k start|restart|graceful|stop]", pad_len, " ");
#endif /* AP_MPM_WANT_SET_GRACEFUL_SHUTDOWN */
#endif
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-v] [-V] [-h] [-l] [-L] [-t] [-T] [-S]",
                 pad_len, " ");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "Options:");

#ifdef SHARED_CORE
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -R directory       : specify an alternate location for "

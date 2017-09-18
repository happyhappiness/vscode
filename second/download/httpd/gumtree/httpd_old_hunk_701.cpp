                 "  -k install        : install an Apache service");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k config         : change startup Options of an Apache "
                 "service");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k uninstall      : uninstall an Apache service");
#endif

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -e level          : show startup errors of level "
                 "(see LogLevel)");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,

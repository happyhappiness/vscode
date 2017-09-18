                 "  -k install        : install an Apache service");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k config         : change startup Options of an Apache "
                 "service");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k uninstall      : uninstall an Apache service");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -w                : hold open the console window on error");
#endif

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -e level          : show startup errors of level "
                 "(see LogLevel)");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -n name            : set screen name");
#endif
#ifdef WIN32
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -n name            : set service name and use its "
                 "ServerConfigFile");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k start           : tell Apache to start");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k restart         : tell running Apache to do a graceful "
                 "restart");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,

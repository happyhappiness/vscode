                 "  -C \"directive\"    : process directive before reading "
                 "config files");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -c \"directive\"    : process directive after reading "
                 "config files");

#ifdef NETWARE
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -n name           : set screen name");
#endif
#ifdef WIN32
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -n name           : set service name and use its "
                 "ServerConfigFile");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k start          : tell Apache to start");

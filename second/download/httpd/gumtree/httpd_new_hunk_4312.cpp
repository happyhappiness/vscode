                 "  -S                 : a synonym for -t -D DUMP_VHOSTS -D DUMP_RUN_CFG");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t -D DUMP_MODULES : show all loaded modules ");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -M                 : a synonym for -t -D DUMP_MODULES");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t -D DUMP_INCLUDES: show all included configuration files");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t                 : run syntax check for config files");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -T                 : start without DocumentRoot(s) check");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -X                 : debug mode (only one worker, do not detach)");


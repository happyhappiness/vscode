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
                 "shared object files");
#endif

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -D name            : define a name for use in "
                 "<IfDefine name> directives");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -d directory       : specify an alternate initial "
                 "ServerRoot");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -f file            : specify an alternate ServerConfigFile");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -C \"directive\"     : process directive before reading "
                 "config files");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -c \"directive\"     : process directive after reading "
                 "config files");

#ifdef NETWARE
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
                 "  -k stop|shutdown   : tell running Apache to shutdown");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k install         : install an Apache service");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k config          : change startup Options of an Apache "
                 "service");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k uninstall       : uninstall an Apache service");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -w                 : hold open the console window on error");
#endif

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -e level           : show startup errors of level "
                 "(see LogLevel)");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -E file            : log startup errors to file");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -v                 : show version number");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -V                 : show compile settings");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -h                 : list available command line options "
                 "(this page)");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -l                 : list compiled in modules");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -L                 : list available configuration "
                 "directives");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t -D DUMP_VHOSTS  : show parsed settings (currently only "
                 "vhost settings)");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -S                 : a synonym for -t -D DUMP_VHOSTS");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t -D DUMP_MODULES : show all loaded modules ");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -M                 : a synonym for -t -D DUMP_MODULES");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t                 : run syntax check for config files");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                "  -T                 : start without DocumentRoot(s) check");

    destroy_and_exit_process(process, 1);
}
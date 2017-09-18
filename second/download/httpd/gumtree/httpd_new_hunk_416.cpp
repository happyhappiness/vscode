        pad[i] = ' ';
    }

    pad[i] = '\0';

#ifdef SHARED_CORE
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL ,
                 "Usage: %s [-R directory] [-D name] [-d directory] [-f file]",
                 bin);
#else
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "Usage: %s [-D name] [-d directory] [-f file]", bin);
#endif

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %s [-C \"directive\"] [-c \"directive\"]", pad);

#ifdef WIN32
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %s [-k start|restart|stop|shutdown]", pad);
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %s [-k install|config|uninstall] [-n service_name]",
                 pad);
#endif
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
                 "shared object files");
#endif

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -D name           : define a name for use in "
                 "<IfDefine name> directives");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -d directory      : specify an alternate initial "
                 "ServerRoot");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -f file           : specify an alternate ServerConfigFile");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -C \"directive\"    : process directive before reading "
                 "config files");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -c \"directive\"    : process directive after reading "
                 "config files");

#ifdef WIN32
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -n name           : set service name and use its "
                 "ServerConfigFile");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k start          : tell Apache to start");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k restart        : tell running Apache to do a graceful "
                 "restart");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -k stop|shutdown  : tell running Apache to shutdown");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
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
                 "  -E file           : log startup errors to file");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -v                : show version number");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -V                : show compile settings");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -h                : list available command line options "
                 "(this page)");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -l                : list compiled in modules");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -L                : list available configuration "
                 "directives");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t -D DUMP_VHOSTS : show parsed settings (currently only "
                 "vhost settings)");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -t                : run syntax check for config files");

    destroy_and_exit_process(process, 1);
}

int main(int argc, const char * const argv[])
{

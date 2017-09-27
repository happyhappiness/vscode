    return process;
}

static void usage(process_rec *process)
{
    const char *bin = process->argv[0];
    int pad_len = strlen(bin);

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "Usage: %s [-D name] [-d directory] [-f file]", bin);

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-C \"directive\"] [-c \"directive\"]", pad_len, " ");

#ifdef WIN32
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-w] [-k start|restart|stop|shutdown] [-n service_name]",
                 pad_len, " ");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-k install|config|uninstall] [-n service_name]",
                 pad_len, " ");
#else
/* XXX not all MPMs support signalling the server in general or graceful-stop
 * in particular
 */
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-k start|restart|graceful|graceful-stop|stop]",
                 pad_len, " ");
#endif
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "       %*s [-v] [-V] [-h] [-l] [-L] [-t] [-T] [-S] [-X]",
                 pad_len, " ");
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "Options:");

    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                 "  -D name            : define a name for use in "
                 "<IfDefine name> directives");

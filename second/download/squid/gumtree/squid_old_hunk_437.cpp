    }

    pid = readPidFile();

    if (pid > 1) {
#if USE_WIN32_SERVICE

        if (opt_signal_service) {
            WIN32_sendSignal(opt_send_signal);
            exit(0);
        } else
#if _SQUID_MSWIN_
        {
            fprintf(stderr, "%s: ERROR: Could not send ", APP_SHORTNAME);
            fprintf(stderr, "signal to Squid Service:\n");
            fprintf(stderr, "missing -n command line switch.\n");
            exit(1);
        }

        /* NOTREACHED */
#endif

#endif

        if (kill(pid, opt_send_signal) &&
                /* ignore permissions if just running check */
                !(opt_send_signal == 0 && errno == EPERM)) {
            fprintf(stderr, "%s: ERROR: Could not send ", APP_SHORTNAME);
            fprintf(stderr, "signal %d to process %d: %s\n",
                    opt_send_signal, (int) pid, xstrerror());

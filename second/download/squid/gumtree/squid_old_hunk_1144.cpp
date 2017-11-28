    return 0;
}

static void
sendSignal(void)
{
    pid_t pid;
    debug_log = stderr;

    if (strcmp(Config.pidFilename, "none") == 0) {
        debugs(0, DBG_IMPORTANT, "No pid_filename specified. Trusting you know what you are doing.");
    }

    pid = readPidFile();

    if (pid > 1) {
#if USE_WIN32_SERVICE
        if (opt_signal_service) {
            WIN32_sendSignal(opt_send_signal);
            exit(0);
        } else {
            fprintf(stderr, "%s: ERROR: Could not send ", APP_SHORTNAME);
            fprintf(stderr, "signal to Squid Service:\n");
            fprintf(stderr, "missing -n command line switch.\n");
            exit(1);
        }
        /* NOTREACHED */
#endif

        if (kill(pid, opt_send_signal) &&
                /* ignore permissions if just running check */
                !(opt_send_signal == 0 && errno == EPERM)) {
            fprintf(stderr, "%s: ERROR: Could not send ", APP_SHORTNAME);
            fprintf(stderr, "signal %d to process %d: %s\n",
                    opt_send_signal, (int) pid, xstrerror());
            exit(1);
        }
    } else {
        if (opt_send_signal != SIGTERM) {
            fprintf(stderr, "%s: ERROR: No running copy\n", APP_SHORTNAME);
            exit(1);
        } else {
            fprintf(stderr, "%s: No running copy\n", APP_SHORTNAME);
            exit(0);
        }
    }

    /* signal successfully sent */
    exit(0);
}

#if !_SQUID_WINDOWS_
/*
 * This function is run when Squid is in daemon mode, just
 * before the parent forks and starts up the child process.

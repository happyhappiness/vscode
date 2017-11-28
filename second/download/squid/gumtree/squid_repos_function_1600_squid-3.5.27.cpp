static void
watch_child(char *argv[])
{
#if !_SQUID_WINDOWS_
    char *prog;
#if _SQUID_NEXT_

    union wait status;
#else

    int status;
#endif

    pid_t pid;
#ifdef TIOCNOTTY

    int i;
#endif

    int nullfd;

    if (!IamMasterProcess())
        return;

    openlog(APP_SHORTNAME, LOG_PID | LOG_NDELAY | LOG_CONS, LOG_LOCAL4);

    if ((pid = fork()) < 0)
        syslog(LOG_ALERT, "fork failed: %s", xstrerror());
    else if (pid > 0)
        exit(0);

    if (setsid() < 0)
        syslog(LOG_ALERT, "setsid failed: %s", xstrerror());

    closelog();

#ifdef TIOCNOTTY

    if ((i = open("/dev/tty", O_RDWR | O_TEXT)) >= 0) {
        ioctl(i, TIOCNOTTY, NULL);
        close(i);
    }

#endif

    /*
     * RBCOLLINS - if cygwin stackdumps when squid is run without
     * -N, check the cygwin1.dll version, it needs to be AT LEAST
     * 1.1.3.  execvp had a bit overflow error in a loop..
     */
    /* Connect stdio to /dev/null in daemon mode */
    nullfd = open(_PATH_DEVNULL, O_RDWR | O_TEXT);

    if (nullfd < 0)
        fatalf(_PATH_DEVNULL " %s\n", xstrerror());

    dup2(nullfd, 0);

    if (Debug::log_stderr < 0) {
        dup2(nullfd, 1);
        dup2(nullfd, 2);
    }

    // handle shutdown notifications from kids
    squid_signal(SIGUSR1, sig_shutdown, SA_RESTART);

    if (Config.workers > 128) {
        syslog(LOG_ALERT, "Suspiciously high workers value: %d",
               Config.workers);
        // but we keep going in hope that user knows best
    }
    TheKids.init();

    syslog(LOG_NOTICE, "Squid Parent: will start %d kids", (int)TheKids.count());

    // keep [re]starting kids until it is time to quit
    for (;;) {
        mainStartScript(argv[0]);

        // start each kid that needs to be [re]started; once
        for (int i = TheKids.count() - 1; i >= 0; --i) {
            Kid& kid = TheKids.get(i);
            if (!kid.shouldRestart())
                continue;

            if ((pid = fork()) == 0) {
                /* child */
                openlog(APP_SHORTNAME, LOG_PID | LOG_NDELAY | LOG_CONS, LOG_LOCAL4);
                prog = argv[0];
                argv[0] = const_cast<char*>(kid.name().termedBuf());
                execvp(prog, argv);
                syslog(LOG_ALERT, "execvp failed: %s", xstrerror());
            }

            kid.start(pid);
            syslog(LOG_NOTICE, "Squid Parent: %s process %d started",
                   kid.name().termedBuf(), pid);
        }

        /* parent */
        openlog(APP_SHORTNAME, LOG_PID | LOG_NDELAY | LOG_CONS, LOG_LOCAL4);

        squid_signal(SIGINT, SIG_IGN, SA_RESTART);

#if _SQUID_NEXT_

        pid = wait3(&status, 0, NULL);

#else

        pid = waitpid(-1, &status, 0);

#endif
        // Loop to collect all stopped kids before we go to sleep below.
        do {
            Kid* kid = TheKids.find(pid);
            if (kid) {
                kid->stop(status);
                if (kid->calledExit()) {
                    syslog(LOG_NOTICE,
                           "Squid Parent: %s process %d exited with status %d",
                           kid->name().termedBuf(),
                           kid->getPid(), kid->exitStatus());
                } else if (kid->signaled()) {
                    syslog(LOG_NOTICE,
                           "Squid Parent: %s process %d exited due to signal %d with status %d",
                           kid->name().termedBuf(),
                           kid->getPid(), kid->termSignal(), kid->exitStatus());
                } else {
                    syslog(LOG_NOTICE, "Squid Parent: %s process %d exited",
                           kid->name().termedBuf(), kid->getPid());
                }
                if (kid->hopeless()) {
                    syslog(LOG_NOTICE, "Squid Parent: %s process %d will not"
                           " be restarted due to repeated, frequent failures",
                           kid->name().termedBuf(), kid->getPid());
                }
            } else {
                syslog(LOG_NOTICE, "Squid Parent: unknown child process %d exited", pid);
            }
#if _SQUID_NEXT_
        } while ((pid = wait3(&status, WNOHANG, NULL)) > 0);
#else
        }
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0);
#endif

        if (!TheKids.someRunning() && !TheKids.shouldRestartSome()) {
            leave_suid();
            // XXX: Master process has no main loop and, hence, should not call
            // RegisteredRunner::startShutdown which promises a loop iteration.
            RunRegisteredHere(RegisteredRunner::finishShutdown);
            enter_suid();

            if (TheKids.someSignaled(SIGINT) || TheKids.someSignaled(SIGTERM)) {
                syslog(LOG_ALERT, "Exiting due to unexpected forced shutdown");
                exit(1);
            }

            if (TheKids.allHopeless()) {
                syslog(LOG_ALERT, "Exiting due to repeated, frequent failures");
                exit(1);
            }

            exit(0);
        }

        squid_signal(SIGINT, SIG_DFL, SA_RESTART);
        sleep(3);
    }
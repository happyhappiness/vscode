
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
            DeactivateRegistered(rrAfterConfig);
            DeactivateRegistered(rrClaimMemoryNeeds);
            DeactivateRegistered(rrFinalizeConfig);
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


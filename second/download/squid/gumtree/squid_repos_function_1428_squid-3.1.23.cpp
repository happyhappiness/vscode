static void
watch_child(char *argv[])
{
#ifndef _SQUID_MSWIN_
    char *prog;
    int failcount = 0;
    time_t start;
    time_t stop;
#ifdef _SQUID_NEXT_

    union wait status;
#else

    int status;
#endif

    pid_t pid;
#ifdef TIOCNOTTY

    int i;
#endif

    int nullfd;

    if (*(argv[0]) == '(')
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

    for (;;) {
        mainStartScript(argv[0]);

        if ((pid = fork()) == 0) {
            /* child */
            openlog(APP_SHORTNAME, LOG_PID | LOG_NDELAY | LOG_CONS, LOG_LOCAL4);
            prog = xstrdup(argv[0]);
            argv[0] = xstrdup("(squid)");
            execvp(prog, argv);
            syslog(LOG_ALERT, "execvp failed: %s", xstrerror());
        }

        /* parent */
        openlog(APP_SHORTNAME, LOG_PID | LOG_NDELAY | LOG_CONS, LOG_LOCAL4);

        syslog(LOG_NOTICE, "Squid Parent: child process %d started", pid);

        time(&start);

        squid_signal(SIGINT, SIG_IGN, SA_RESTART);

#ifdef _SQUID_NEXT_

        pid = wait3(&status, 0, NULL);

#else

        pid = waitpid(-1, &status, 0);

#endif

        time(&stop);

        if (WIFEXITED(status)) {
            syslog(LOG_NOTICE,
                   "Squid Parent: child process %d exited with status %d",
                   pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            syslog(LOG_NOTICE,
                   "Squid Parent: child process %d exited due to signal %d with status %d",
                   pid, WTERMSIG(status), WEXITSTATUS(status));
        } else {
            syslog(LOG_NOTICE, "Squid Parent: child process %d exited", pid);
        }

        if (stop - start < 10)
            failcount++;
        else
            failcount = 0;

        if (failcount == 5) {
            syslog(LOG_ALERT, "Exiting due to repeated, frequent failures");
            exit(1);
        }

        if (WIFEXITED(status))
            if (WEXITSTATUS(status) == 0)
                exit(0);

        if (WIFSIGNALED(status)) {
            switch (WTERMSIG(status)) {

            case SIGKILL:
                exit(0);
                break;

            case SIGINT:
            case SIGTERM:
                syslog(LOG_ALERT, "Exiting due to unexpected forced shutdown");
                exit(1);
                break;

            default:
                break;
            }
        }

        squid_signal(SIGINT, SIG_DFL, SA_RESTART);
        sleep(3);
    }

    /* NOTREACHED */
#endif /* _SQUID_MSWIN_ */

}
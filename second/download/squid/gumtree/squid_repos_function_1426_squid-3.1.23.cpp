static void
mainStartScript(const char *prog)
{
    char script[SQUID_MAXPATHLEN];
    char *t;
    size_t sl = 0;
    pid_t cpid;
    pid_t rpid;
    xstrncpy(script, prog, MAXPATHLEN);

    if ((t = strrchr(script, '/'))) {
        *(++t) = '\0';
        sl = strlen(script);
    }

    xstrncpy(&script[sl], squid_start_script, MAXPATHLEN - sl);

    if ((cpid = fork()) == 0) {
        /* child */
        execl(script, squid_start_script, (char *)NULL);
        _exit(-1);
    } else {
        do {
#ifdef _SQUID_NEXT_
            union wait status;
            rpid = wait3(&status, 0, NULL);
#else

            int status;
            rpid = waitpid(-1, &status, 0);
#endif

        } while (rpid != cpid);
    }
}
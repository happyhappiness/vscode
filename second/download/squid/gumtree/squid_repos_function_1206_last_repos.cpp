static void
mainStartScript(const char *prog)
{
    char script[MAXPATHLEN];
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
            PidStatus status;
            rpid = WaitForOnePid(cpid, status, 0);
        } while (rpid != cpid);
    }
}
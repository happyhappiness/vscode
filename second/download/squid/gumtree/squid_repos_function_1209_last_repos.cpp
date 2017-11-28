static void
GoIntoBackground()
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        int xerrno = errno;
        syslog(LOG_ALERT, "fork failed: %s", xstrerr(xerrno));
        // continue anyway, mimicking --foreground mode (XXX?)
    } else if (pid > 0) {
        // parent
        exit(EXIT_SUCCESS);
    }
    // child, running as a background daemon (or a failed-to-fork parent)
}
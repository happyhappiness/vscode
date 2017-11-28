    _db_print("WARNING: %s\n", message);
}

void
sig_child(int sig)
{
#ifndef _SQUID_MSWIN_
#ifdef _SQUID_NEXT_
    union wait status;
#else

    int status;
#endif

    pid_t pid;

    do {
#ifdef _SQUID_NEXT_
        pid = wait3(&status, WNOHANG, NULL);
#else

        pid = waitpid(-1, &status, WNOHANG);
#endif
        /* no debug() here; bad things happen if the signal is delivered during _db_print() */
#if HAVE_SIGACTION

    } while (pid > 0);

#else


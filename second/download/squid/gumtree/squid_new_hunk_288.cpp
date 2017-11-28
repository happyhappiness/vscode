    _db_print("WARNING: %s\n", message);
}

void
sig_child(int sig)
{
#if !_SQUID_MSWIN_
#if _SQUID_NEXT_
    union wait status;
#else

    int status;
#endif

    pid_t pid;

    do {
#if _SQUID_NEXT_
        pid = wait3(&status, WNOHANG, NULL);
#else

        pid = waitpid(-1, &status, WNOHANG);
#endif
        /* no debugs() here; bad things happen if the signal is delivered during _db_print() */
#if HAVE_SIGACTION

    } while (pid > 0);

#else


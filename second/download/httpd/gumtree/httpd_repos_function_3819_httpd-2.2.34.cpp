apr_status_t apr_proc_detach(int daemonize)
{
#if 0
    int x;
    pid_t pgrp;

    chdir("/");
#if !defined(MPE) && !defined(OS2) && !defined(TPF) && !defined(BEOS)
/* Don't detach for MPE because child processes can't survive the death of
   the parent. */
    if ((x = fork()) > 0)
        exit(0);
    else if (x == -1) {
        perror("fork");
        fprintf(stderr, "unable to fork new process\n");
        exit(1);  /* we can't do anything here, so just exit. */
    }
/*    RAISE_SIGSTOP(DETACH);*/
#endif
#if APR_HAVE_SETSID
    if ((pgrp = setsid()) == -1) {
        return errno;
    }
#elif defined(NEXT) || defined(NEWSOS)
    if (setpgrp(0, getpid()) == -1 || (pgrp = getpgrp(0)) == -1) {
        return errno;
    }
#elif defined(OS2) || defined(TPF)
    /* OS/2 don't support process group IDs */
    pgrp = getpid();
#elif defined(MPE)
    /* MPE uses negative pid for process group */
    pgrp = -getpid();
#else
    if ((pgrp = setpgid(0, 0)) == -1) {
        return errno;
    }
#endif

    /* close out the standard file descriptors */
    if (freopen("/dev/null", "r", stdin) == NULL) {
        return errno;
        /* continue anyhow -- note we can't close out descriptor 0 because we
         * have nothing to replace it with, and if we didn't have a descriptor
         * 0 the next file would be created with that value ... leading to
         * havoc.
         */
    }
    if (freopen("/dev/null", "w", stdout) == NULL) {
        return errno;
    }
     /* We are going to reopen this again in a little while to the error
      * log file, but better to do it twice and suffer a small performance
      * hit for consistancy than not reopen it here.
      */
    if (freopen("/dev/null", "w", stderr) == NULL) {
        return errno;
    }
#endif
    return APR_SUCCESS;
}
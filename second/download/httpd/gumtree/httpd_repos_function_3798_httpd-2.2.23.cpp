static void remove_sync_sigs(sigset_t *sig_mask)
{
#ifdef SIGABRT
    sigdelset(sig_mask, SIGABRT);
#endif
#ifdef SIGBUS
    sigdelset(sig_mask, SIGBUS);
#endif
#ifdef SIGEMT
    sigdelset(sig_mask, SIGEMT);
#endif
#ifdef SIGFPE
    sigdelset(sig_mask, SIGFPE);
#endif
#ifdef SIGILL
    sigdelset(sig_mask, SIGILL);
#endif
#ifdef SIGIOT
    sigdelset(sig_mask, SIGIOT);
#endif
#ifdef SIGPIPE
    sigdelset(sig_mask, SIGPIPE);
#endif
#ifdef SIGSEGV
    sigdelset(sig_mask, SIGSEGV);
#endif
#ifdef SIGSYS
    sigdelset(sig_mask, SIGSYS);
#endif
#ifdef SIGTRAP
    sigdelset(sig_mask, SIGTRAP);
#endif

/* the rest of the signals removed from the mask in this function
 * absolutely must be removed; you cannot block synchronous signals
 * (requirement of pthreads API)
 *
 * SIGUSR2 is being removed from the mask for the convenience of
 * Purify users (Solaris, HP-UX, SGI) since Purify uses SIGUSR2
 */
#ifdef SIGUSR2
    sigdelset(sig_mask, SIGUSR2);
#endif
}
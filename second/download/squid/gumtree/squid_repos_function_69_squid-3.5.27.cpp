SigFunc*
Signal( int signo, SigFunc* newhandler, bool doInterrupt )
// purpose: install reliable signals
// paramtr: signo (IN): signal for which a handler is to be installed
//          newhandler (IN): function pointer to the signal handler
//          doInterrupt (IN): interrupted system calls wanted!
// returns: the old signal handler, or SIG_ERR in case of error.
{
    struct sigaction action, old;

    memset( &old, 0, sizeof(old) );
    memset( &action, 0, sizeof(action) );

    // action.sa_handler = newhandler; I HATE TYPE-OVERCORRECTNESS !
    memmove( &action.sa_handler, &newhandler, sizeof(SigFunc*) );
    sigemptyset( &action.sa_mask );

    if ( signo == SIGCHLD ) {
        action.sa_flags |= SA_NOCLDSTOP;

#ifdef SA_NODEFER
        action.sa_flags |= SA_NODEFER;   // SYSV: don't block current signal
#endif
    }

    if ( signo == SIGALRM || doInterrupt ) {
#ifdef SA_INTERRUPT
        action.sa_flags |= SA_INTERRUPT; // SunOS, obsoleted by POSIX
#endif
    } else {
#ifdef SA_RESTART
        action.sa_flags |= SA_RESTART;   // BSD, SVR4
#endif
    }

    return ( sigaction( signo, &action, &old ) < 0 ) ?
           (SigFunc*) SIG_ERR :
           (SigFunc*) old.sa_handler;
}
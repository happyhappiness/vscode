void
shut_down(int sig)
{
    do_shutdown = sig == SIGINT ? -1 : 1;
    ShutdownSignal = sig;
#if defined(SIGTTIN)
    if (SIGTTIN == sig)
        shutdown_status = 1;
#endif

#if !_SQUID_WINDOWS_
#if !HAVE_SIGACTION
    signal(sig, shut_down);
#endif
#endif
}
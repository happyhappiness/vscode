void
master_shutdown(int sig)
{
    do_shutdown = 1;
    ShutdownSignal = sig;

#if !_SQUID_WINDOWS_
#if !HAVE_SIGACTION
    signal(sig, master_shutdown);
#endif
#endif

}
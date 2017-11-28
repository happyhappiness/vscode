void
reconfigure(int sig)
{
    do_reconfigure = 1;
    ReconfigureSignal = sig;
#if !_SQUID_WINDOWS_
#if !HAVE_SIGACTION

    signal(sig, reconfigure);
#endif
#endif
}
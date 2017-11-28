void
reconfigure(int sig)
{
    do_reconfigure = 1;
#ifndef _SQUID_MSWIN_
#if !HAVE_SIGACTION

    signal(sig, reconfigure);
#endif
#endif
}
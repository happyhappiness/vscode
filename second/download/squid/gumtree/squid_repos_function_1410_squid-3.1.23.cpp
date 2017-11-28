void
rotate_logs(int sig)
{
    do_rotate = 1;
#ifndef _SQUID_MSWIN_
#if !HAVE_SIGACTION

    signal(sig, rotate_logs);
#endif
#endif
}
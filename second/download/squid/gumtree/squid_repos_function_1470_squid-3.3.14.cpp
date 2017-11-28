void
rotate_logs(int sig)
{
    do_rotate = 1;
    RotateSignal = sig;
#if !_SQUID_WINDOWS_
#if !HAVE_SIGACTION

    signal(sig, rotate_logs);
#endif
#endif
}
void
sig_child(int sig)
{
    do_handle_stopped_child = 1;

#if !_SQUID_WINDOWS_
#if !HAVE_SIGACTION
    signal(sig, sig_child);
#endif
#endif
}
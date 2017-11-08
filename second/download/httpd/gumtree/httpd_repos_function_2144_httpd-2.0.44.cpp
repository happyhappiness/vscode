static void restart(int sig)
{
#ifndef WIN32
    ap_start_restart(sig == AP_SIG_GRACEFUL);
#else
    ap_start_restart(1);
#endif
}
static void restart(int sig)
{
    ap_start_restart(sig == AP_SIG_GRACEFUL);
}
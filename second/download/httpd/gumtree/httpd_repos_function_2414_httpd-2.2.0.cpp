static void sig_term(int sig)
{
    ap_start_shutdown(sig == AP_SIG_GRACEFUL_STOP);
}
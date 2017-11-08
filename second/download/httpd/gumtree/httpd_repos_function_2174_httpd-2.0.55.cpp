static void sig_term(int sig)
{
    ap_start_shutdown();
}
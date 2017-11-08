static void sig_term(int sig)
{
    if (ap_my_pid == parent_pid) {
        ap_start_shutdown();
    }
    else {
        signal_threads(ST_GRACEFUL);
    }
}
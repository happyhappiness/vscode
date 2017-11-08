static void stop_listening(int sig)
{
    mpm_state = AP_MPMQ_STOPPING;
    ap_close_listeners();

    /* For a graceful stop, we want the child to exit when done */
    die_now = 1;
}
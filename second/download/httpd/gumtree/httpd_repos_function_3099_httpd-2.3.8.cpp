static void stop_listening(int sig)
{
    ap_close_listeners();

    /* For a graceful stop, we want the child to exit when done */
    die_now = 1;
}

static void just_die(int sig)
{
    clean_child_exit(0);
}

/* volatile because it's updated from a signal handler */
static int volatile die_now = 0;

static void stop_listening(int sig)
{
    retained->mpm->mpm_state = AP_MPMQ_STOPPING;
    ap_close_listeners_ex(my_bucket->listeners);

    /* For a graceful stop, we want the child to exit when done */
    die_now = 1;
}

/*****************************************************************
 * Child process main loop.
 * The following vars are static to avoid getting clobbered by longjmp();
 * they are really private to child_main.
 */


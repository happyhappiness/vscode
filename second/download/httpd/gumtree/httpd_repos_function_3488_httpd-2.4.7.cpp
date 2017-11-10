static void sig_term(int sig)
{
    if (shutdown_pending == 1) {
        /* Um, is this _probably_ not an error, if the user has
         * tried to do a shutdown twice quickly, so we won't
         * worry about reporting it.
         */
        return;
    }
    shutdown_pending = 1;

    DBPRINT0 ("waiting for threads\n");
    while (wait_to_finish) {
        apr_thread_yield();
    }
    DBPRINT0 ("goodbye\n");
}
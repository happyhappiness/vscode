static void sig_term(int sig)
{
    if (shutdown_pending == 1) {
        /* Um, is this _probably_ not an error, if the user has
         * tried to do a shutdown twice quickly, so we won't
         * worry about reporting it.
         */
        return;
    }
    mpm_state = AP_MPMQ_STOPPING;
    shutdown_pending = 1;
    retained->is_graceful = (sig == AP_SIG_GRACEFUL_STOP);
}
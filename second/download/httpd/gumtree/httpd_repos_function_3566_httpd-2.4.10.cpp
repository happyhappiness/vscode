static void restart(int sig)
{
    if (restart_pending == 1) {
        /* Probably not an error - don't bother reporting it */
        return;
    }
    mpm_state = AP_MPMQ_STOPPING;
    restart_pending = 1;
    retained->is_graceful = (sig == AP_SIG_GRACEFUL);
}
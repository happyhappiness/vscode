static void sig_restart(int sig)
{
    retained_data->mpm_state = AP_MPMQ_STOPPING;
    if (retained_data->restart_pending
            && (retained_data->is_ungraceful
                || sig == AP_SIG_GRACEFUL)) {
        /* Already handled */
        return;
    }

    retained_data->restart_pending = 1;
    if (sig != AP_SIG_GRACEFUL) {
        retained_data->is_ungraceful = 1;
    }
}
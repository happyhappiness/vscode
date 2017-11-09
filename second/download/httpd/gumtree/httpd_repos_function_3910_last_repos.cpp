static void sig_term(int sig)
{
    retained_data->mpm_state = AP_MPMQ_STOPPING;
    if (retained_data->shutdown_pending
            && (retained_data->is_ungraceful
                || sig == AP_SIG_GRACEFUL_STOP)) {
        /* Already handled */
        return;
    }

    retained_data->shutdown_pending = 1;
    if (sig != AP_SIG_GRACEFUL_STOP) {
        retained_data->is_ungraceful = 1;
    }
}
static apr_status_t unset_signals(void *unused)
{
    retained_data->shutdown_pending = retained_data->restart_pending = 0;
    retained_data->was_graceful = !retained_data->is_ungraceful;
    retained_data->is_ungraceful = 0;

    return APR_SUCCESS;
}
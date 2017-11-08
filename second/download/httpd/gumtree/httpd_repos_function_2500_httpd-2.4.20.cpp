apr_status_t h2_task_init(apr_pool_t *pool, server_rec *s)
{
    h2_task_logio_add_bytes_in = APR_RETRIEVE_OPTIONAL_FN(ap_logio_add_bytes_in);
    h2_task_logio_add_bytes_out = APR_RETRIEVE_OPTIONAL_FN(ap_logio_add_bytes_out);

    return APR_SUCCESS;
}
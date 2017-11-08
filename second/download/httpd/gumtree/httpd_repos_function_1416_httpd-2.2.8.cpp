static apr_status_t warn_rx_free(void *p)
{
    ap_pregfree((apr_pool_t*)p, warn_rx);
    return APR_SUCCESS;
}
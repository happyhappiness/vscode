static int http_post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    apr_uint64_t val;
    if (ap_mpm_query(AP_MPMQ_IS_ASYNC, &async_mpm) != APR_SUCCESS) {
        async_mpm = 0;
    }
    ap_random_insecure_bytes(&val, sizeof(val));
    ap_multipart_boundary = apr_psprintf(p, "%0" APR_UINT64_T_HEX_FMT, val);

    return OK;
}
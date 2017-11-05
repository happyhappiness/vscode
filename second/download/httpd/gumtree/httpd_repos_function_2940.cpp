static apr_status_t cleanup_mx_hash(void *dummy)
{
    mxcfg_by_type = NULL;
    return APR_SUCCESS;
}
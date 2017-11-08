static apr_status_t reload_conf_hash(void *baton)
{
    ap_config_hash = NULL;
    return APR_SUCCESS;
}
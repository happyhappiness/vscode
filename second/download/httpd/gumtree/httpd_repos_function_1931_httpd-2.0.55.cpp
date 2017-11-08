static apr_status_t reset_version(void *dummy)
{
    version_locked = 0;
    ap_server_tokens = SrvTk_FULL;
    server_version = NULL;
    return APR_SUCCESS;
}
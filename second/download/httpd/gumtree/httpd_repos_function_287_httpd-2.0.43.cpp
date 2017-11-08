static apr_status_t dav_cleanup_providers(void *ctx)
{
    dav_repos_providers = NULL;
    return APR_SUCCESS;
}
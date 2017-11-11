static apr_status_t cleanup_global_providers(void *ctx)
{
    global_providers = NULL;
    global_providers_names = NULL;
    return APR_SUCCESS;
}
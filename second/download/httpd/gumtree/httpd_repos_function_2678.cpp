static apr_status_t destroy_cache(void *data)
{
    if (socache_instance) {
        socache_provider->destroy(socache_instance, (server_rec*)data);
        socache_instance = NULL;
    }
    return APR_SUCCESS;
}
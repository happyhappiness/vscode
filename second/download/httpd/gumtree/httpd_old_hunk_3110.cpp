/*
 * Make sure the shared memory is cleaned
 */
static int post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp,
                       server_rec *s)
{
    void *data;
    const char *userdata_key = "slotmem_shm_post_config";

    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        apr_pool_userdata_set((const void *)1, userdata_key,
                               apr_pool_cleanup_null, s->process->pool);
        return OK;
    }

    slotmem_shm_initialize_cleanup(p);
    return OK;
}

static int pre_config(apr_pool_t *p, apr_pool_t *plog,
                      apr_pool_t *ptemp)
{
    apr_pool_t *global_pool;
    apr_status_t rv;

    rv = apr_pool_create(&global_pool, NULL);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
            "Fatal error: unable to create global pool for shared slotmem");
        return rv;
    }
    slotmem_shm_initgpool(global_pool);
    return OK;
}

static void ap_slotmem_shm_register_hook(apr_pool_t *p)
{
    const ap_slotmem_provider_t *storage = slotmem_shm_getstorage();
    ap_register_provider(p, AP_SLOTMEM_PROVIDER_GROUP, "shared", "0", storage);
    ap_hook_post_config(post_config, NULL, NULL, APR_HOOK_LAST);
    ap_hook_pre_config(pre_config, NULL, NULL, APR_HOOK_MIDDLE);
}

AP_DECLARE_MODULE(slotmem_shm) = {
    STANDARD20_MODULE_STUFF,

/*
 * Make sure the shared memory is cleaned
 */
static int post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp,
                       server_rec *s)
{
    slotmem_shm_initialize_cleanup(p);
    return OK;
}

static int pre_config(apr_pool_t *p, apr_pool_t *plog,
                      apr_pool_t *ptemp)
{
    slotmem_shm_initgpool(p);
    return OK;
}

static void ap_slotmem_shm_register_hook(apr_pool_t *p)
{
    const ap_slotmem_provider_t *storage = slotmem_shm_getstorage();
    ap_register_provider(p, AP_SLOTMEM_PROVIDER_GROUP, "shm",
                         AP_SLOTMEM_PROVIDER_VERSION, storage);
    ap_hook_post_config(post_config, NULL, NULL, APR_HOOK_LAST);
    ap_hook_pre_config(pre_config, NULL, NULL, APR_HOOK_MIDDLE);
}

AP_DECLARE_MODULE(slotmem_shm) = {
    STANDARD20_MODULE_STUFF,

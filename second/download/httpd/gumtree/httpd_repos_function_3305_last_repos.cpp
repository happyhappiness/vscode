static void ap_slotmem_shm_register_hook(apr_pool_t *p)
{
    const ap_slotmem_provider_t *storage = slotmem_shm_getstorage();
    ap_register_provider(p, AP_SLOTMEM_PROVIDER_GROUP, "shm",
                         AP_SLOTMEM_PROVIDER_VERSION, storage);
    ap_hook_post_config(post_config, NULL, NULL, APR_HOOK_LAST);
    ap_hook_pre_config(pre_config, NULL, NULL, APR_HOOK_MIDDLE);
}
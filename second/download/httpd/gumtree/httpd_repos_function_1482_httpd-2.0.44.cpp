static void register_hooks(apr_pool_t *p)
{
    ap_hook_post_config(mem_cache_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    /* cache initializer */
    /* cache_hook_init(cache_mem_init, NULL, NULL, APR_HOOK_MIDDLE);  */
    cache_hook_create_entity(create_entity, NULL, NULL, APR_HOOK_MIDDLE);
    cache_hook_open_entity(open_entity,  NULL, NULL, APR_HOOK_MIDDLE);
    cache_hook_remove_url(remove_url, NULL, NULL, APR_HOOK_MIDDLE);
}
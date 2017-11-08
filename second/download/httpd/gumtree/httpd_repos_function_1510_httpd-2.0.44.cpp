static void disk_cache_register_hook(apr_pool_t *p)
{
    /* cache initializer */
    cache_hook_create_entity(create_entity, NULL, NULL, APR_HOOK_MIDDLE);
    cache_hook_open_entity(open_entity,  NULL, NULL, APR_HOOK_MIDDLE);
/*    cache_hook_remove_entity(remove_entity, NULL, NULL, APR_HOOK_MIDDLE); */
}
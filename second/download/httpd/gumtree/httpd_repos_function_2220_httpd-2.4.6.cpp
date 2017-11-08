static void register_hooks(apr_pool_t *p)
{
    ap_hook_post_config(ef_init, NULL, NULL, APR_HOOK_MIDDLE);
}
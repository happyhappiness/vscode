static void register_hooks(apr_pool_t *p)
{
    ap_hook_post_config(post_config, NULL, NULL, APR_HOOK_LAST);
    ap_hook_translate_name(xlate_name, NULL, NULL, APR_HOOK_FIRST);
}
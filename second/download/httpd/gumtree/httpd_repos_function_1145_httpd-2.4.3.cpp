static void register_hooks(apr_pool_t *p)
{
    ap_hook_handler(file_cache_handler, NULL, NULL, APR_HOOK_LAST);
    ap_hook_post_config(file_cache_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_translate_name(file_cache_xlat, NULL, NULL, APR_HOOK_MIDDLE);
    /* This trick doesn't work apparently because the translate hooks
       are single shot. If the core_hook returns OK, then our hook is
       not called.
    ap_hook_translate_name(file_cache_xlat, aszPre, NULL, APR_HOOK_MIDDLE);
    */

}
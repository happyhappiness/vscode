static void register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(ap_register_rewrite_mapfunc);

    ap_hook_handler(handler_redirect, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_config(pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(init_child, NULL, NULL, APR_HOOK_MIDDLE);

    ap_hook_fixups(hook_fixup, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_translate_name(hook_uri2file, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_type_checker(hook_mimetype, NULL, NULL, APR_HOOK_MIDDLE);
}
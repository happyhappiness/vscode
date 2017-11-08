static void register_hooks(apr_pool_t *p)
{
    /* fixup after mod_proxy, so that the proxied url will not
     * escaped accidentally by mod_proxy's fixup.
     */
    static const char * const aszPre[]={ "mod_proxy.c", NULL };

    /* make the hashtable before registering the function, so that
     * other modules are prevented from accessing uninitialized memory.
     */
    mapfunc_hash = apr_hash_make(p);
    APR_REGISTER_OPTIONAL_FN(ap_register_rewrite_mapfunc);

    ap_hook_handler(handler_redirect, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_config(pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(init_child, NULL, NULL, APR_HOOK_MIDDLE);

    ap_hook_fixups(hook_fixup, aszPre, NULL, APR_HOOK_FIRST);
    ap_hook_fixups(hook_mimetype, NULL, NULL, APR_HOOK_LAST);
    ap_hook_translate_name(hook_uri2file, NULL, NULL, APR_HOOK_FIRST);
}
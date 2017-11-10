static void register_hooks(apr_pool_t *p)
{
    /* fixup after mod_proxy, so that the proxied url will not
     * escaped accidentally by mod_proxy's fixup.
     */
    static const char * const aszPre[]={ "mod_proxy.c", NULL };

    /* check type before mod_mime, so that [T=foo/bar] will not be
     * overridden by AddType definitions.
     */
    static const char * const ct_aszSucc[]={ "mod_mime.c", NULL };

    APR_REGISTER_OPTIONAL_FN(ap_register_rewrite_mapfunc);

    ap_hook_handler(handler_redirect, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_config(pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(init_child, NULL, NULL, APR_HOOK_MIDDLE);

    ap_hook_fixups(hook_fixup, aszPre, NULL, APR_HOOK_FIRST);
    ap_hook_translate_name(hook_uri2file, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_type_checker(hook_mimetype, NULL, ct_aszSucc, APR_HOOK_MIDDLE);
}
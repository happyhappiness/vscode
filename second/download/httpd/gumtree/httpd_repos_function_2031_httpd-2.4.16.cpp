static void register_hooks(apr_pool_t *p)
{
    /* fixup before mod_rewrite, so that the proxied url will not
     * escaped accidentally by our fixup.
     */
    static const char * const aszSucc[] = { "mod_rewrite.c", NULL};
    /* Only the mpm_winnt has child init hook handler.
     * make sure that we are called after the mpm
     * initializes.
     */
    static const char *const aszPred[] = { "mpm_winnt.c", "mod_proxy_balancer.c", NULL};

    /* handler */
    ap_hook_handler(proxy_handler, NULL, NULL, APR_HOOK_FIRST);
    /* filename-to-URI translation */
    ap_hook_translate_name(proxy_trans, aszSucc, NULL, APR_HOOK_FIRST);
    /* walk <Proxy > entries and suppress default TRACE behavior */
    ap_hook_map_to_storage(proxy_map_location, NULL,NULL, APR_HOOK_FIRST);
    /* fixups */
    ap_hook_fixups(proxy_fixup, NULL, aszSucc, APR_HOOK_FIRST);
    /* post read_request handling */
    ap_hook_post_read_request(proxy_detect, NULL, NULL, APR_HOOK_FIRST);
    /* pre config handling */
    ap_hook_pre_config(proxy_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    /* post config handling */
    ap_hook_post_config(proxy_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    /* child init handling */
    ap_hook_child_init(child_init, aszPred, NULL, APR_HOOK_MIDDLE);

    /* register optional functions within proxy_util.c */
    proxy_util_register_hooks(p);
}
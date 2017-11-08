static void register_hooks(apr_pool_t *p)
{
    static const char * const cfgPost[]={ "http_core.c", NULL };
    static const char * const parsePre[]={ "mod_proxy.c", NULL };

    ap_hook_post_config(initialize_module, NULL, cfgPost, APR_HOOK_MIDDLE);
    ap_hook_child_init(initialize_child, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_read_request(parse_hdr_and_update_nc, parsePre, NULL, APR_HOOK_MIDDLE);
    ap_hook_check_user_id(authenticate_digest_user, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_auth_checker(digest_check_auth, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_fixups(add_auth_info, NULL, NULL, APR_HOOK_MIDDLE);
}
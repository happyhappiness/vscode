static void privileges_hooks(apr_pool_t *pool)
{
    ap_hook_post_read_request(privileges_req, NULL, NULL,
                              APR_HOOK_REALLY_FIRST);
    ap_hook_header_parser(privileges_req, NULL, NULL, APR_HOOK_REALLY_FIRST);
    ap_hook_drop_privileges(privileges_drop_first, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_drop_privileges(privileges_drop_last, NULL, NULL, APR_HOOK_LAST);
    ap_hook_post_config(privileges_postconf, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_config(privileges_init, NULL, NULL, APR_HOOK_FIRST);
}
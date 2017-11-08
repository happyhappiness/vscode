static void register_hooks(apr_pool_t *p)
{
    ap_hook_header_parser(match_headers, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_read_request(match_headers, NULL, NULL, APR_HOOK_MIDDLE);
    /* post config handling */
    ap_hook_post_config(setenvif_post_config, NULL, NULL, APR_HOOK_MIDDLE);
}
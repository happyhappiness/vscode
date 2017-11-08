static void register_hooks(apr_pool_t *p)
{
    ap_hook_header_parser(match_headers, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_read_request(match_headers, NULL, NULL, APR_HOOK_MIDDLE);

    is_header_regex_regex = ap_pregcomp(p, "^[-A-Za-z0-9_]*$",
                                        (AP_REG_EXTENDED | AP_REG_NOSUB ));
    ap_assert(is_header_regex_regex != NULL);
}
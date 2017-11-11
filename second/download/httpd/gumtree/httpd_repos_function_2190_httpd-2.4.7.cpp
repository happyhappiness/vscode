static void proxy_html_hooks(apr_pool_t *p)
{
    static const char *aszSucc[] = { "mod_filter.c", NULL };
    ap_register_output_filter_protocol("proxy-html", proxy_html_filter,
                                       NULL, AP_FTYPE_RESOURCE,
                          AP_FILTER_PROTO_CHANGE|AP_FILTER_PROTO_CHANGE_LENGTH);
    /* move this to pre_config so old_expr is available to interpret
     * old-style conditions on URL maps.
     */
    ap_hook_pre_config(mod_proxy_html, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_insert_filter(proxy_html_insert, NULL, aszSucc, APR_HOOK_MIDDLE);
}
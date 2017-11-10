void ap_expr_init(apr_pool_t *p)
{
    ap_hook_expr_lookup(core_expr_lookup, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_expr_lookup(expr_lookup_not_found, NULL, NULL, APR_HOOK_REALLY_LAST);
    ap_hook_post_config(ap_expr_post_config, NULL, NULL, APR_HOOK_MIDDLE);
}
    return;
}
static void register_hooks(apr_pool_t *p)
{
    ap_register_output_filter("MOD_EXPIRES", expires_filter, NULL,
                              AP_FTYPE_CONTENT_SET);
    ap_hook_insert_error_filter(expires_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_insert_filter(expires_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA expires_module =
{
    STANDARD20_MODULE_STUFF,

};

static void charset_register_hooks(apr_pool_t *p)
{
    ap_hook_fixups(find_code_page, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_insert_filter(xlate_insert_filter, NULL, NULL, APR_HOOK_REALLY_LAST);
    ap_register_output_filter(XLATEOUT_FILTER_NAME, xlate_out_filter, NULL,
                              AP_FTYPE_RESOURCE);
    ap_register_input_filter(XLATEIN_FILTER_NAME, xlate_in_filter, NULL,
                             AP_FTYPE_RESOURCE);
}

module AP_MODULE_DECLARE_DATA charset_lite_module =
{
    STANDARD20_MODULE_STUFF,

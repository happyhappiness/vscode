static void register_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(header_pre_config,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_insert_filter(ap_headers_insert_output_filter, NULL, NULL, APR_HOOK_LAST);
    ap_hook_insert_error_filter(ap_headers_insert_error_filter, NULL, NULL, APR_HOOK_LAST);
    ap_hook_fixups(ap_headers_fixup, NULL, NULL, APR_HOOK_LAST);
    ap_register_output_filter("FIXUP_HEADERS_OUT", ap_headers_output_filter,
                              NULL, AP_FTYPE_CONTENT_SET);
    ap_register_output_filter("FIXUP_HEADERS_ERR", ap_headers_error_filter,
                              NULL, AP_FTYPE_CONTENT_SET);
}
static void register_hooks(apr_pool_t *p)
{
    keep_body_input_filter_handle =
        ap_register_input_filter(KEEP_BODY_FILTER, keep_body_filter,
                                 NULL, AP_FTYPE_RESOURCE);
    kept_body_input_filter_handle =
        ap_register_input_filter(KEPT_BODY_FILTER, kept_body_filter,
                                 kept_body_filter_init, AP_FTYPE_RESOURCE);
    ap_hook_insert_filter(ap_request_insert_filter, NULL, NULL, APR_HOOK_LAST);
    APR_REGISTER_OPTIONAL_FN(ap_request_insert_filter);
    APR_REGISTER_OPTIONAL_FN(ap_request_remove_filter);
}
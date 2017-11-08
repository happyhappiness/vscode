static void register_hooks(apr_pool_t *p)
{
    ap_register_output_filter(sed_filter_name, sed_response_filter, NULL,
                              AP_FTYPE_RESOURCE);
    ap_register_input_filter(sed_filter_name, sed_request_filter, NULL,
                             AP_FTYPE_RESOURCE);
}
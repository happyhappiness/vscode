static void register_hooks(apr_pool_t *p) {
    ap_register_output_filter(bufferFilterName, buffer_out_filter, NULL,
            AP_FTYPE_CONTENT_SET);
    ap_register_input_filter(bufferFilterName, buffer_in_filter, NULL,
            AP_FTYPE_CONTENT_SET);
}
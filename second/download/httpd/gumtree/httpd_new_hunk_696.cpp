     * filters
     */
    ap_hook_insert_filter(core_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);

    ap_core_input_filter_handle =
        ap_register_input_filter("CORE_IN", core_input_filter,
                                 NULL, AP_FTYPE_NETWORK);
    ap_net_time_filter_handle =
        ap_register_input_filter("NET_TIME", net_time_filter,
                                 NULL, AP_FTYPE_PROTOCOL);
    ap_content_length_filter_handle =
        ap_register_output_filter("CONTENT_LENGTH", ap_content_length_filter,
                                  NULL, AP_FTYPE_PROTOCOL);
    ap_core_output_filter_handle =
        ap_register_output_filter("CORE", core_output_filter,
                                  NULL, AP_FTYPE_NETWORK);
    ap_subreq_core_filter_handle =
        ap_register_output_filter("SUBREQ_CORE", ap_sub_req_output_filter,
                                  NULL, AP_FTYPE_CONTENT_SET);
    ap_old_write_func =
        ap_register_output_filter("OLD_WRITE", ap_old_write_filter,
                                  NULL, AP_FTYPE_RESOURCE - 10);
}

AP_DECLARE_DATA module core_module = {
    STANDARD20_MODULE_STUFF,
    create_core_dir_config,       /* create per-directory config structure */
    merge_core_dir_configs,       /* merge per-directory config structures */

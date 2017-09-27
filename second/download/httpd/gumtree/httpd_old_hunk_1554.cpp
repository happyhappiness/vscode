    ap_register_output_filter(XLATEOUT_FILTER_NAME, xlate_out_filter, NULL,
                              AP_FTYPE_RESOURCE);
    ap_register_input_filter(XLATEIN_FILTER_NAME, xlate_in_filter, NULL,
                             AP_FTYPE_RESOURCE);
}

module AP_MODULE_DECLARE_DATA charset_lite_module =
{
    STANDARD20_MODULE_STUFF,
    create_charset_dir_conf,
    merge_charset_dir_conf,
    NULL,
    NULL,

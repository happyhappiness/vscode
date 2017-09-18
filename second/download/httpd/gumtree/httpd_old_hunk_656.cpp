{
    APR_REGISTER_OPTIONAL_FN(ap_ssi_get_tag_and_value);
    APR_REGISTER_OPTIONAL_FN(ap_ssi_parse_string);
    APR_REGISTER_OPTIONAL_FN(ap_register_include_handler);
    ap_hook_post_config(include_post_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
    ap_hook_fixups(include_fixup, NULL, NULL, APR_HOOK_LAST);
    ap_register_output_filter("INCLUDES", includes_filter, AP_FTYPE_RESOURCE);
}

module AP_MODULE_DECLARE_DATA include_module =
{
    STANDARD20_MODULE_STUFF,
    create_includes_dir_config,   /* dir config creater */

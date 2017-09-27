    ap_hook_post_config(include_post_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
    ap_hook_fixups(include_fixup, NULL, NULL, APR_HOOK_LAST);
    ap_register_output_filter("INCLUDES", includes_filter, includes_setup,
                              AP_FTYPE_RESOURCE);
}

AP_DECLARE_MODULE(include) =
{
    STANDARD20_MODULE_STUFF,
    create_includes_dir_config,   /* dir config creater */
    NULL,                         /* dir merger --- default is to override */
    create_includes_server_config,/* server config */
    NULL,                         /* merge server config */

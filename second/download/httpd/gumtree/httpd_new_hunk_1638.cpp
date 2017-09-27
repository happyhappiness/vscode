    ap_register_output_filter("MOD_EXPIRES", expires_filter, NULL,
                              AP_FTYPE_CONTENT_SET-2);
    ap_hook_insert_error_filter(expires_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_insert_filter(expires_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);
}

AP_DECLARE_MODULE(expires) =
{
    STANDARD20_MODULE_STUFF,
    create_dir_expires_config,  /* dir config creater */
    merge_expires_dir_configs,  /* dir merger --- default is to override */
    NULL,                       /* server config */
    NULL,                       /* merge server configs */

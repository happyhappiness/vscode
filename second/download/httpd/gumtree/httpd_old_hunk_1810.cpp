                                  NULL, AP_FTYPE_CONTENT_SET);
    ap_old_write_func =
        ap_register_output_filter("OLD_WRITE", ap_old_write_filter,
                                  NULL, AP_FTYPE_RESOURCE - 10);
}

AP_DECLARE_DATA module core_module = {
    STANDARD20_MODULE_STUFF,
    create_core_dir_config,       /* create per-directory config structure */
    merge_core_dir_configs,       /* merge per-directory config structures */
    create_core_server_config,    /* create per-server config structure */
    merge_core_server_configs,    /* merge per-server config structures */
    core_cmds,                    /* command apr_table_t */
    register_hooks                /* register hooks */

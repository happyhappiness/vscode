    proxy_hook_canon_handler(proxy_ftp_canon, NULL, NULL, APR_HOOK_MIDDLE);
    /* filters */
    ap_register_output_filter("PROXY_SEND_DIR", proxy_send_dir_filter,
                              NULL, AP_FTYPE_RESOURCE);
}

module AP_MODULE_DECLARE_DATA proxy_ftp_module = {
    STANDARD20_MODULE_STUFF,
    NULL,                       /* create per-directory config structure */
    NULL,                       /* merge per-directory config structures */
    NULL,                       /* create per-server config structure */
    NULL,                       /* merge per-server config structures */
    NULL,                       /* command apr_table_t */
    ap_proxy_ftp_register_hook  /* register hooks */
};

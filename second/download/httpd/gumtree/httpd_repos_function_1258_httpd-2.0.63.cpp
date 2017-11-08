static void ap_proxy_ftp_register_hook(apr_pool_t *p)
{
    /* hooks */
    proxy_hook_scheme_handler(ap_proxy_ftp_handler, NULL, NULL, APR_HOOK_MIDDLE);
    proxy_hook_canon_handler(ap_proxy_ftp_canon, NULL, NULL, APR_HOOK_MIDDLE);
    /* filters */
    ap_register_output_filter("PROXY_SEND_DIR", ap_proxy_send_dir_filter,
                              NULL, AP_FTYPE_RESOURCE);
}
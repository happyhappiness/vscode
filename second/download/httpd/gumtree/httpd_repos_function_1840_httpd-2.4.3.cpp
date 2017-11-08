static void ap_proxy_ftp_register_hook(apr_pool_t *p)
{
    /* hooks */
    proxy_hook_scheme_handler(proxy_ftp_handler, NULL, NULL, APR_HOOK_MIDDLE);
    proxy_hook_canon_handler(proxy_ftp_canon, NULL, NULL, APR_HOOK_MIDDLE);
    /* filters */
    ap_register_output_filter("PROXY_SEND_DIR", proxy_send_dir_filter,
                              NULL, AP_FTYPE_RESOURCE);
    /* Compile the output format of "ls -s1" as a fallback for non-unix ftp listings */
    ls_regex = ap_pregcomp(p, LS_REG_PATTERN, AP_REG_EXTENDED);
    ap_assert(ls_regex != NULL);
}
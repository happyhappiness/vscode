    /* hooks */
    proxy_hook_scheme_handler(proxy_ftp_handler, NULL, NULL, APR_HOOK_MIDDLE);
    proxy_hook_canon_handler(proxy_ftp_canon, NULL, NULL, APR_HOOK_MIDDLE);
    /* filters */
    ap_register_output_filter("PROXY_SEND_DIR", proxy_send_dir_filter,
                              NULL, AP_FTYPE_RESOURCE);
}

static const command_rec proxy_ftp_cmds[] =
{
    AP_INIT_FLAG("ProxyFtpListOnWildcard", set_ftp_list_on_wildcard, NULL,
     RSRC_CONF|ACCESS_CONF, "Whether wildcard characters in a path cause mod_proxy_ftp to list the files instead of trying to get them. Defaults to on."),

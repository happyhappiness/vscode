}

static void register_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(header_pre_config,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_insert_filter(ap_headers_insert_output_filter, NULL, NULL, APR_HOOK_LAST);
    ap_hook_fixups(ap_headers_fixup, NULL, NULL, APR_HOOK_LAST);
    ap_register_output_filter("FIXUP_HEADERS_OUT", ap_headers_output_filter,
                              NULL, AP_FTYPE_CONTENT_SET);
}

module AP_MODULE_DECLARE_DATA headers_module =
{
    STANDARD20_MODULE_STUFF,
    create_headers_dir_config,  /* dir config creater */
    merge_headers_config,       /* dir merger --- default is to override */
    create_headers_config,      /* server config */
    merge_headers_config,       /* merge server configs */
    headers_cmds,               /* command apr_table_t */
    register_hooks		/* register hooks */
};

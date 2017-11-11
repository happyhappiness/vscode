static int cgi_post_config(apr_pool_t *p, apr_pool_t *plog,
                                apr_pool_t *ptemp, server_rec *s)
{
    cgi_pfn_reg_with_ssi = APR_RETRIEVE_OPTIONAL_FN(ap_register_include_handler);
    cgi_pfn_gtv          = APR_RETRIEVE_OPTIONAL_FN(ap_ssi_get_tag_and_value);
    cgi_pfn_ps           = APR_RETRIEVE_OPTIONAL_FN(ap_ssi_parse_string);

    if ((cgi_pfn_reg_with_ssi) && (cgi_pfn_gtv) && (cgi_pfn_ps)) {
        /* Required by mod_include filter. This is how mod_cgi registers
         *   with mod_include to provide processing of the exec directive.
         */
        cgi_pfn_reg_with_ssi("exec", handle_exec);
    }

    /* This is the means by which unusual (non-unix) os's may find alternate
     * means to run a given command (e.g. shebang/registry parsing on Win32)
     */
    cgi_build_command    = APR_RETRIEVE_OPTIONAL_FN(ap_cgi_build_command);
    if (!cgi_build_command) {
        cgi_build_command = default_build_command;
    }
    return OK;
}
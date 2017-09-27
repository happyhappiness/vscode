    access_compat_ap_satisfies = APR_RETRIEVE_OPTIONAL_FN(access_compat_ap_satisfies);

    set_banner(pconf);
    ap_setup_make_content_type(pconf);
    ap_setup_auth_internal(ptemp);
    if (!sys_privileges) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL, APLOGNO(00136)
                     "Server MUST relinquish startup privileges before "
                     "accepting connections.  Please ensure mod_unixd "
                     "or other system security module is loaded.");
        return !OK;
    }
    apr_pool_cleanup_register(pconf, NULL, ap_mpm_end_gen_helper,
                              apr_pool_cleanup_null);
    return OK;
}

static void core_insert_filter(request_rec *r)
{
    core_dir_config *conf = (core_dir_config *)
                            ap_get_core_module_config(r->per_dir_config);
    const char *filter, *filters = conf->output_filters;

    if (filters) {
        while (*filters && (filter = ap_getword(r->pool, &filters, ';'))) {
            ap_add_output_filter(filter, NULL, r, r->connection);
        }

    }
}

/* Optional function coming from mod_logio, used for logging of output
 * traffic
 */
APR_OPTIONAL_FN_TYPE(ap_logio_add_bytes_out) *ap__logio_add_bytes_out;
APR_OPTIONAL_FN_TYPE(authz_some_auth_required) *ap__authz_ap_some_auth_required;

/* Insist that at least one module will undertake to provide system
 * security by dropping startup privileges.
 */
static int sys_privileges = 0;
AP_DECLARE(int) ap_sys_privileges_handlers(int inc)
{
    sys_privileges += inc;
    return sys_privileges;
}

static int core_pre_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
{
    ap_mutex_init(pconf);
    return APR_SUCCESS;
}

static int core_post_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    ap__logio_add_bytes_out = APR_RETRIEVE_OPTIONAL_FN(ap_logio_add_bytes_out);
    ident_lookup = APR_RETRIEVE_OPTIONAL_FN(ap_ident_lookup);
    ap__authz_ap_some_auth_required = APR_RETRIEVE_OPTIONAL_FN(authz_some_auth_required);
    authn_ap_auth_type = APR_RETRIEVE_OPTIONAL_FN(authn_ap_auth_type);
    authn_ap_auth_name = APR_RETRIEVE_OPTIONAL_FN(authn_ap_auth_name);
    access_compat_ap_satisfies = APR_RETRIEVE_OPTIONAL_FN(access_compat_ap_satisfies);

    set_banner(pconf);
    ap_setup_make_content_type(pconf);
    ap_setup_auth_internal(ptemp);
    if (!sys_privileges) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL,
                     "Server MUST relinquish startup privileges before "
                     "accepting connections.  Please ensure mod_unixd "
                     "or other system security module is loaded.");
        return !OK;
    }
    return OK;
}

static void core_insert_filter(request_rec *r)
{
    core_dir_config *conf = (core_dir_config *)

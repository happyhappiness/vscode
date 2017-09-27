    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "[%" APR_PID_T_FMT "] auth_ldap authenticate: accepting %s", getpid(), user);

    return AUTH_GRANTED;
}

/*
 * Authorisation Phase
 * -------------------
 *
 * After checking whether the username and password are correct, we need
 * to check whether that user is authorised to view this resource. The
 * require directive is used to do this:
 *
 *  require valid-user          Any authenticated is allowed in.
 *  require user <username>     This particular user is allowed in.
 *  require group <groupname>   The user must be a member of this group
 *                              in order to be allowed in.
 *  require dn <dn>             The user must have the following DN in the
 *                              LDAP tree to be let in.
 *
 */
static int authz_ldap_check_user_access(request_rec *r)
{
    int result = 0;
    authn_ldap_request_t *req =
        (authn_ldap_request_t *)ap_get_module_config(r->request_config, &authnz_ldap_module);
    authn_ldap_config_t *sec =
        (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);

    util_ldap_connection_t *ldc = NULL;
    int m = r->method_number;

    const apr_array_header_t *reqs_arr = ap_requires(r);
    require_line *reqs = reqs_arr ? (require_line *)reqs_arr->elts : NULL;

    register int x;
    const char *t;
    char *w, *value;
    int method_restricted = 0;
    int required_ldap = 0;

    char filtbuf[FILTER_LENGTH];
    const char *dn = NULL;
    const char **vals = NULL;

/*
    if (!sec->enabled) {
        return DECLINED;
    }
*/

    if (!sec->have_ldap_url) {
        return DECLINED;
    }

    /* pre-scan for ldap-* requirements so we can get out of the way early */
    for(x=0; x < reqs_arr->nelts; x++) {
        if (! (reqs[x].method_mask & (AP_METHOD_BIT << m))) {
            continue;
        }

        t = reqs[x].requirement;
        w = ap_getword_white(r->pool, &t);

        if (strncmp(w, "ldap-",5) == 0) {
            required_ldap = 1;
            break;
        }
    }

    if (!required_ldap) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authorise: declining to authorise (no ldap requirements)", getpid());
        return DECLINED;
    }



    if (sec->host) {
        ldc = util_ldap_connection_find(r, sec->host, sec->port,
                                       sec->binddn, sec->bindpw, sec->deref,
                                       sec->secure);
        apr_pool_cleanup_register(r->pool, ldc,
                                  authnz_ldap_cleanup_connection_close,
                                  apr_pool_cleanup_null);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authorise: no sec->host - weird...?", getpid());
        return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
    }

    /*
     * If there are no elements in the group attribute array, the default should be
     * member and uniquemember; populate the array now.
     */

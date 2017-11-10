static authz_status ldapuser_check_authorization(request_rec *r,
                                                 const char *require_args,
                                                 const void *parsed_require_args)
{
    int result = 0;
    authn_ldap_request_t *req =
        (authn_ldap_request_t *)ap_get_module_config(r->request_config, &authnz_ldap_module);
    authn_ldap_config_t *sec =
        (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);

    util_ldap_connection_t *ldc = NULL;

    const char *err = NULL;
    const ap_expr_info_t *expr = parsed_require_args;
    const char *require;

    const char *t;
    char *w;

    char filtbuf[FILTER_LENGTH];
    const char *dn = NULL;

    if (!r->user) {
        return AUTHZ_DENIED_NO_USER;
    }

    if (!sec->have_ldap_url) {
        return AUTHZ_DENIED;
    }

    if (sec->host) {
        ldc = get_connection_for_authz(r, LDAP_COMPARE);
        apr_pool_cleanup_register(r->pool, ldc,
                                  authnz_ldap_cleanup_connection_close,
                                  apr_pool_cleanup_null);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01698)
                      "auth_ldap authorize: no sec->host - weird...?");
        return AUTHZ_DENIED;
    }

    /*
     * If we have been authenticated by some other module than mod_authnz_ldap,
     * the req structure needed for authorization needs to be created
     * and populated with the userid and DN of the account in LDAP
     */


    if (!strlen(r->user)) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01699)
            "ldap authorize: Userid is blank, AuthType=%s",
            r->ap_auth_type);
    }

    if(!req) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01700)
            "ldap authorize: Creating LDAP req structure");

        req = (authn_ldap_request_t *)apr_pcalloc(r->pool,
            sizeof(authn_ldap_request_t));

        /* Build the username filter */
        authn_ldap_build_filter(filtbuf, r, r->user, NULL, sec);

        /* Search for the user DN */
        result = util_ldap_cache_getuserdn(r, ldc, sec->url, sec->basedn,
             sec->scope, sec->attributes, filtbuf, &dn, &(req->vals));

        /* Search failed, log error and return failure */
        if(result != LDAP_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01701)
                "auth_ldap authorise: User DN not found, %s", ldc->reason);
            return AUTHZ_DENIED;
        }

        ap_set_module_config(r->request_config, &authnz_ldap_module, req);
        req->dn = apr_pstrdup(r->pool, dn);
        req->user = r->user;

    }

    if (req->dn == NULL || strlen(req->dn) == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01702)
                      "auth_ldap authorize: require user: user's DN has not "
                      "been defined; failing authorization");
        return AUTHZ_DENIED;
    }

    require = ap_expr_str_exec(r, expr, &err);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02585)
                      "auth_ldap authorize: require user: Can't evaluate expression: %s",
                      err);
        return AUTHZ_DENIED;
    }

    /*
     * First do a whole-line compare, in case it's something like
     *   require user Babs Jensen
     */
    result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, require);
    switch(result) {
        case LDAP_COMPARE_TRUE: {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01703)
                          "auth_ldap authorize: require user: authorization "
                          "successful");
            set_request_vars(r, LDAP_AUTHZ);
            return AUTHZ_GRANTED;
        }
        default: {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01704)
                          "auth_ldap authorize: require user: "
                          "authorization failed [%s][%s]",
                          ldc->reason
        ldc = get_connection_for_authz(r, LDAP_COMPARE);
        apr_pool_cleanup_register(r->pool, ldc,
                                  authnz_ldap_cleanup_connection_close,
                                  apr_pool_cleanup_null);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01729)
                      "auth_ldap authorize: no sec->host - weird...?");
        return AUTHZ_DENIED;
    }

    /*
     * If we have been authenticated by some other module than mod_auth_ldap,
     * the req structure needed for authorization needs to be created
     * and populated with the userid and DN of the account in LDAP
     */

    if (!strlen(r->user)) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01730)
            "ldap authorize: Userid is blank, AuthType=%s",
            r->ap_auth_type);
    }

    if(!req) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01731)
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
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01732)
                "auth_ldap authorise: User DN not found with filter %s: %s", filtbuf, ldc->reason);
            return AUTHZ_DENIED;
        }

        ap_set_module_config(r->request_config, &authnz_ldap_module, req);
        req->dn = apr_pstrdup(r->pool, dn);
        req->user = r->user;
    }

    if (req->dn == NULL || strlen(req->dn) == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01733)
                      "auth_ldap authorize: require ldap-attribute: user's DN "
                      "has not been defined; failing authorization");
        return AUTHZ_DENIED;
    }

    t = require_args;
    while (t[0]) {
        w = ap_getword(r->pool, &t, '=');
        value = ap_getword_conf(r->pool, &t);

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01734)
                      "auth_ldap authorize: checking attribute %s has value %s",
                      w, value);
        result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, w, value);
        switch(result) {
            case LDAP_COMPARE_TRUE: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01735)
                              "auth_ldap authorize: "
                              "require attribute: authorization successful");
                set_request_vars(r, LDAP_AUTHZ);
                return AUTHZ_GRANTED;
            }
            default: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01736)
                              "auth_ldap authorize: require attribute: "
                              "authorization failed [%s][%s]",
                              ldc->reason, ldap_err2string(result));
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01737)
                  "auth_ldap authorize attribute: authorization denied for "
                  "user %s to %s",
                  r->user, r->uri);

    return AUTHZ_DENIED;
}

static authz_status ldapfilter_check_authorization(request_rec *r,
                                                   const char *require_args,
                                                   const void *parsed_require_args)
{
    int result = 0;
    authn_ldap_request_t *req =
        (authn_ldap_request_t *)ap_get_module_config(r->request_config, &authnz_ldap_module);
    authn_ldap_config_t *sec =
        (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);

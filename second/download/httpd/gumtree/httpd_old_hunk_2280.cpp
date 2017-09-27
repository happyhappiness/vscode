        req->dn = apr_pstrdup(r->pool, dn);
        req->user = r->user;
    }

    if (req->dn == NULL || strlen(req->dn) == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authorize: "
                      "require ldap-filter: user's DN has not been defined; failing authorization",
                      getpid());
        return AUTHZ_DENIED;
    }

    t = require_args;

    if (t[0]) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authorize: checking filter %s",
                      getpid(), t);

        /* Build the username filter */
        authn_ldap_build_filter(filtbuf, r, req->user, t, sec);

        /* Search for the user DN */
        result = util_ldap_cache_getuserdn(r, ldc, sec->url, sec->basedn,
             sec->scope, sec->attributes, filtbuf, &dn, &(req->vals));

        /* Make sure that the filtered search returned the correct user dn */
        if (result == LDAP_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "[%" APR_PID_T_FMT "] auth_ldap authorize: checking dn match %s",
                          getpid(), dn);
            if (sec->compare_as_user) {
                /* ldap-filter is the only authz that requires a search and a compare */
                apr_pool_cleanup_kill(r->pool, ldc, authnz_ldap_cleanup_connection_close);
                authnz_ldap_cleanup_connection_close(ldc);
                ldc = get_connection_for_authz(r, LDAP_COMPARE);
            }
            result = util_ldap_cache_comparedn(r, ldc, sec->url, req->dn, dn,
                                               sec->compare_dn_on_server);
        }

        switch(result) {
            case LDAP_COMPARE_TRUE: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                              0, r, "[%" APR_PID_T_FMT "] auth_ldap authorize: "
                              "require ldap-filter: authorization "
                              "successful", getpid());
                set_request_vars(r, LDAP_AUTHZ);
                return AUTHZ_GRANTED;
            }
            case LDAP_FILTER_ERROR: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                              0, r, "[%" APR_PID_T_FMT "] auth_ldap authorize: "
                              "require ldap-filter: %s authorization "
                              "failed [%s][%s]", getpid(),
                              filtbuf, ldc->reason, ldap_err2string(result));
                break;
            }
            default: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                              0, r, "[%" APR_PID_T_FMT "] auth_ldap authorize: "
                              "require ldap-filter: authorization "
                              "failed [%s][%s]", getpid(),
                              ldc->reason, ldap_err2string(result));
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "[%" APR_PID_T_FMT "] auth_ldap authorize filter: authorization denied for user %s to %s",
                  getpid(), r->user, r->uri);

    return AUTHZ_DENIED;
}


/*

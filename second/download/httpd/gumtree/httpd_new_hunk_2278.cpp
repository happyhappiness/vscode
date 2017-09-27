        req->dn = apr_pstrdup(r->pool, dn);
        req->user = r->user;
    }

    if (req->dn == NULL || strlen(req->dn) == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "auth_ldap authorize: require ldap-attribute: user's DN "
                      "has not been defined; failing authorization");
        return AUTHZ_DENIED;
    }

    t = require_args;
    while (t[0]) {
        w = ap_getword(r->pool, &t, '=');
        value = ap_getword_conf(r->pool, &t);

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "auth_ldap authorize: checking attribute %s has value %s",
                      w, value);
        result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, w, value);
        switch(result) {
            case LDAP_COMPARE_TRUE: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "auth_ldap authorize: "
                              "require attribute: authorization successful");
                set_request_vars(r, LDAP_AUTHZ);
                return AUTHZ_GRANTED;
            }
            default: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "auth_ldap authorize: require attribute: "
                              "authorization failed [%s][%s]",
                              ldc->reason, ldap_err2string(result));
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "auth_ldap authorize attribute: authorization denied for "
                  "user %s to %s",
                  r->user, r->uri);

    return AUTHZ_DENIED;
}

static authz_status ldapfilter_check_authorization(request_rec *r,
                                             const char *require_args)

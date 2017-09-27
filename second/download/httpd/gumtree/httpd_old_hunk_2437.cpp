            result = util_ldap_cache_comparedn(r, ldc, sec->url, req->dn, dn,
                                               sec->compare_dn_on_server);
        }

        switch(result) {
            case LDAP_COMPARE_TRUE: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "auth_ldap authorize: require ldap-filter: "
                              "authorization successful");
                set_request_vars(r, LDAP_AUTHZ);
                return AUTHZ_GRANTED;
            }
            case LDAP_FILTER_ERROR: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "auth_ldap authorize: require ldap-filter: "
                              "%s authorization failed [%s][%s]",
                              filtbuf, ldc->reason, ldap_err2string(result));
                break;
            }
            default: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "auth_ldap authorize: require ldap-filter: "
                              "authorization failed [%s][%s]",
                              ldc->reason, ldap_err2string(result));
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "auth_ldap authorize filter: authorization denied for "
                  "user %s to %s",
                  r->user, r->uri);

    return AUTHZ_DENIED;
}

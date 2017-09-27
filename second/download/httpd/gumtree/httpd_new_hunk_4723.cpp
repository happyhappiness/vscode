
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01713)
                  "auth_ldap authorize: require group: testing for group "
                  "membership in \"%s\"",
                  t);

    /* PR52464 exhaust attrs in base group before checking subgroups */
    for (i = 0; i < sec->groupattr->nelts; i++) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01714)
                      "auth_ldap authorize: require group: testing for %s: "
                      "%s (%s)",
                      ent[i].name,
                      sec->group_attrib_is_dn ? req->dn : req->user, t);

        result = util_ldap_cache_compare(r, ldc, sec->url, t, ent[i].name,
                             sec->group_attrib_is_dn ? req->dn : req->user);
        if (result == LDAP_COMPARE_TRUE) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01715)
                          "auth_ldap authorize: require group: "
                          "authorization successful (attribute %s) "
                          "[%s][%d - %s]",
                          ent[i].name, ldc->reason, result,
                          ldap_err2string(result));
            set_request_vars(r, LDAP_AUTHZ);
            return AUTHZ_GRANTED;
        }
        else { 
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01719)
                              "auth_ldap authorize: require group \"%s\": "
                              "didn't match with attr %s [%s][%d - %s]",
                              t, ldc->reason, ent[i].name, result, 
                              ldap_err2string(result));
        }
    }
    
    for (i = 0; i < sec->groupattr->nelts; i++) {
        /* nested groups need searches and compares, so grab a new handle */
        authnz_ldap_cleanup_connection_close(ldc);
        apr_pool_cleanup_kill(r->pool, ldc,authnz_ldap_cleanup_connection_close);

        ldc = get_connection_for_authz(r, LDAP_COMPARE_AND_SEARCH);
        apr_pool_cleanup_register(r->pool, ldc,
                                  authnz_ldap_cleanup_connection_close,
                                  apr_pool_cleanup_null);

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01716)
                       "auth_ldap authorise: require group \"%s\": "
                       "failed [%s][%d - %s], checking sub-groups",
                       t, ldc->reason, result, ldap_err2string(result));

        result = util_ldap_cache_check_subgroups(r, ldc, sec->url, t, ent[i].name,
                                                 sec->group_attrib_is_dn ? req->dn : req->user,
                                                 sec->sgAttributes[0] ? sec->sgAttributes : default_attributes,
                                                 sec->subgroupclasses,
                                                 0, sec->maxNestingDepth);
        if (result == LDAP_COMPARE_TRUE) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01717)
                          "auth_ldap authorise: require group "
                          "(sub-group): authorisation successful "
                          "(attribute %s) [%s][%d - %s]",
                          ent[i].name, ldc->reason, result,
                          ldap_err2string(result));
            set_request_vars(r, LDAP_AUTHZ);
            return AUTHZ_GRANTED;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01718)
                          "auth_ldap authorise: require group "
                          "(sub-group) \"%s\": didn't match with attr %s "
                          "[%s][%d - %s]",
                          t, ldc->reason, ent[i].name, result, 
                          ldap_err2string(result));
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01720)
                  "auth_ldap authorize group: authorization denied for "
                  "user %s to %s",

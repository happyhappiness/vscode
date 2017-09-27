                ldc = get_connection_for_authz(r, LDAP_COMPARE_AND_SEARCH);
                apr_pool_cleanup_register(r->pool, ldc,
                                          authnz_ldap_cleanup_connection_close,
                                          apr_pool_cleanup_null);

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                               "auth_ldap authorise: require group \"%s\": "
                               "failed [%s][%d - %s], checking sub-groups",
                               t, ldc->reason, result, ldap_err2string(result));

                result = util_ldap_cache_check_subgroups(r, ldc, sec->url, t, ent[i].name,
                                                         sec->group_attrib_is_dn ? req->dn : req->user,
                                                         sec->sgAttributes[0] ? sec->sgAttributes : default_attributes,
                                                         sec->subgroupclasses,
                                                         0, sec->maxNestingDepth);
                if(result == LDAP_COMPARE_TRUE) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "auth_ldap authorise: require group "
                                  "(sub-group): authorisation successful "
                                  "(attribute %s) [%s][%d - %s]",
                                  ent[i].name, ldc->reason, result,
                                  ldap_err2string(result));
                    set_request_vars(r, LDAP_AUTHZ);
                    return AUTHZ_GRANTED;
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "auth_ldap authorise: require group "
                                  "(sub-group) \"%s\": authorisation failed "
                                  "[%s][%d - %s]",
                                  t, ldc->reason, result,
                                  ldap_err2string(result));
                }
                break;
            }
            default: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "auth_ldap authorize: require group \"%s\": "
                              "authorization failed [%s][%d - %s]",
                              t, ldc->reason, result, ldap_err2string(result));
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "auth_ldap authorize group: authorization denied for "
                  "user %s to %s",
                  r->user, r->uri);

    return AUTHZ_DENIED;
}

static authz_status ldapdn_check_authorization(request_rec *r,
                                             const char *require_args)

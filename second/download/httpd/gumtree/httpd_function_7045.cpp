static authz_status ldapgroup_check_authorization(request_rec *r,
                                                  const char *require_args,
                                                  const void *parsed_require_args)
{
    int result = 0;
    authn_ldap_request_t *req =
        (authn_ldap_request_t *)ap_get_module_config(r->request_config, &authnz_ldap_module);
    authn_ldap_config_t *sec =
        (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);

    util_ldap_connection_t *ldc = NULL;

    const char *t;

    char filtbuf[FILTER_LENGTH];
    const char *dn = NULL;
    struct mod_auth_ldap_groupattr_entry_t *ent;
    int i;

    if (!r->user) {
        return AUTHZ_DENIED_NO_USER;
    }

    if (!sec->have_ldap_url) {
        return AUTHZ_DENIED;
    }

    if (sec->host) {
        ldc = get_connection_for_authz(r, LDAP_COMPARE); /* for the top-level group only */
        apr_pool_cleanup_register(r->pool, ldc,
                                  authnz_ldap_cleanup_connection_close,
                                  apr_pool_cleanup_null);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01708)
                      "auth_ldap authorize: no sec->host - weird...?");
        return AUTHZ_DENIED;
    }

    /*
     * If there are no elements in the group attribute array, the default should be
     * member and uniquemember; populate the array now.
     */
    if (sec->groupattr->nelts == 0) {
        struct mod_auth_ldap_groupattr_entry_t *grp;
#if APR_HAS_THREADS
        apr_thread_mutex_lock(sec->lock);
#endif
        grp = apr_array_push(sec->groupattr);
        grp->name = "member";
        grp = apr_array_push(sec->groupattr);
        grp->name = "uniqueMember";
#if APR_HAS_THREADS
        apr_thread_mutex_unlock(sec->lock);
#endif
    }

    /*
     * If there are no elements in the sub group classes array, the default
     * should be groupOfNames and groupOfUniqueNames; populate the array now.
     */
    if (sec->subgroupclasses->nelts == 0) {
        struct mod_auth_ldap_groupattr_entry_t *grp;
#if APR_HAS_THREADS
        apr_thread_mutex_lock(sec->lock);
#endif
        grp = apr_array_push(sec->subgroupclasses);
        grp->name = "groupOfNames";
        grp = apr_array_push(sec->subgroupclasses);
        grp->name = "groupOfUniqueNames";
#if APR_HAS_THREADS
        apr_thread_mutex_unlock(sec->lock);
#endif
    }

    /*
     * If we have been authenticated by some other module than mod_auth_ldap,
     * the req structure needed for authorization needs to be created
     * and populated with the userid and DN of the account in LDAP
     */

    if (!strlen(r->user)) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01709)
            "ldap authorize: Userid is blank, AuthType=%s",
            r->ap_auth_type);
    }

    if(!req) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01710)
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
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01711)
                "auth_ldap authorise: User DN not found, %s", ldc->reason);
            return AUTHZ_DENIED;
        }

        ap_set_module_config(r->request_config, &authnz_ldap_module, req);
        req->dn = apr_pstrdup(r->pool, dn);
        req->user = r->user;
    }

    ent = (struct mod_auth_ldap_groupattr_entry_t *) sec->groupattr->elts;

    if (sec->group_attrib_is_dn) {
        if (req->dn == NULL || strlen(req->dn) == 0) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01712)
                          "auth_ldap authorize: require group: user's DN has "
                          "not been defined; failing authorization for user %s",
                          r->user);
            return AUTHZ_DENIED;
        }
    }
    else {
        if (req->user == NULL || strlen(req->user) == 0) {
            /* We weren't called in the authentication phase, so we didn't have a
             * chance to set the user field. Do so now. */
            req->user = r->user;
        }
    }

    t = require_args;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01713)
                  "auth_ldap authorize: require group: testing for group "
                  "membership in \"%s\"",
                  t);

    for (i = 0; i < sec->groupattr->nelts; i++) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01714)
                      "auth_ldap authorize: require group: testing for %s: "
                      "%s (%s)",
                      ent[i].name,
                      sec->group_attrib_is_dn ? req->dn : req->user, t);

        result = util_ldap_cache_compare(r, ldc, sec->url, t, ent[i].name,
                             sec->group_attrib_is_dn ? req->dn : req->user);
        switch(result) {
            case LDAP_COMPARE_TRUE: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01715)
                              "auth_ldap authorize: require group: "
                              "authorization successful (attribute %s) "
                              "[%s][%d - %s]",
                              ent[i].name, ldc->reason, result,
                              ldap_err2string(result));
                set_request_vars(r, LDAP_AUTHZ);
                return AUTHZ_GRANTED;
            }
            case LDAP_NO_SUCH_ATTRIBUTE:
            case LDAP_COMPARE_FALSE: {
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
                if(result == LDAP_COMPARE_TRUE) {
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
                                  "(sub-group) \"%s\": authorisation failed "
                                  "[%s][%d - %s]",
                                  t, ldc->reason, result,
                                  ldap_err2string(result));
                }
                break;
            }
            default: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01719)
                              "auth_ldap authorize: require group \"%s\": "
                              "authorization failed [%s][%d - %s]",
                              t, ldc->reason, result, ldap_err2string(result));
            }
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01720)
                  "auth_ldap authorize group: authorization denied for "
                  "user %s to %s",
                  r->user, r->uri);

    return AUTHZ_DENIED;
}
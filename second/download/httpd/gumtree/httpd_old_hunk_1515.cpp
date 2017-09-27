
        /* Build the username filter */
        authn_ldap_build_filter(filtbuf, r, r->user, NULL, sec);

        /* Search for the user DN */
        result = util_ldap_cache_getuserdn(r, ldc, sec->url, sec->basedn,
             sec->scope, sec->attributes, filtbuf, &dn, &vals);

        /* Search failed, log error and return failure */
        if(result != LDAP_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                "auth_ldap authorise: User DN not found, %s", ldc->reason);
            return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
        }

        req = (authn_ldap_request_t *)apr_pcalloc(r->pool,
            sizeof(authn_ldap_request_t));
        ap_set_module_config(r->request_config, &authnz_ldap_module, req);
        req->dn = apr_pstrdup(r->pool, dn);
        req->user = r->user;
    }

    /* Loop through the requirements array until there's no elements
     * left, or something causes a return from inside the loop */
    for(x=0; x < reqs_arr->nelts; x++) {
        if (! (reqs[x].method_mask & (AP_METHOD_BIT << m))) {
            continue;
        }
        method_restricted = 1;

        t = reqs[x].requirement;
        w = ap_getword_white(r->pool, &t);

        if (strcmp(w, "ldap-user") == 0) {
            if (req->dn == NULL || strlen(req->dn) == 0) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                              "require user: user's DN has not been defined; failing authorisation",
                              getpid());
                return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
            }
            /*
             * First do a whole-line compare, in case it's something like
             *   require user Babs Jensen
             */
            result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, t);
            switch(result) {
                case LDAP_COMPARE_TRUE: {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                  "require user: authorisation successful", getpid());
                    return OK;
                }
                default: {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "[%" APR_PID_T_FMT "] auth_ldap authorise: require user: "
                                  "authorisation failed [%s][%s]", getpid(),
                                  ldc->reason, ldap_err2string(result));
                }
            }
            /*
             * Now break apart the line and compare each word on it
             */
            while (t[0]) {
                w = ap_getword_conf(r->pool, &t);
                result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, w);
                switch(result) {
                    case LDAP_COMPARE_TRUE: {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                      "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                      "require user: authorisation successful", getpid());
                        return OK;
                    }
                    default: {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                      "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                      "require user: authorisation failed [%s][%s]",
                                      getpid(), ldc->reason, ldap_err2string(result));
                    }
                }
            }
        }
        else if (strcmp(w, "ldap-dn") == 0) {
            if (req->dn == NULL || strlen(req->dn) == 0) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                              "require dn: user's DN has not been defined; failing authorisation",
                              getpid());
                return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
            }

            result = util_ldap_cache_comparedn(r, ldc, sec->url, req->dn, t, sec->compare_dn_on_server);
            switch(result) {
                case LDAP_COMPARE_TRUE: {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                  "require dn: authorisation successful", getpid());
                    return OK;
                }
                default: {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                  "require dn \"%s\": LDAP error [%s][%s]",
                                  getpid(), t, ldc->reason, ldap_err2string(result));
                }
            }
        }
        else if (strcmp(w, "ldap-group") == 0) {
            struct mod_auth_ldap_groupattr_entry_t *ent = (struct mod_auth_ldap_groupattr_entry_t *) sec->groupattr->elts;
            int i;

            if (sec->group_attrib_is_dn) {
                if (req->dn == NULL || strlen(req->dn) == 0) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "[%" APR_PID_T_FMT "] auth_ldap authorise: require group: "
                                  "user's DN has not been defined; failing authorisation",
                                  getpid());
                    return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
                }
            }
            else {
                if (req->user == NULL || strlen(req->user) == 0) {
                    /* We weren't called in the authentication phase, so we didn't have a
                     * chance to set the user field. Do so now. */
                    req->user = r->user;
                }
            }

            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "[%" APR_PID_T_FMT "] auth_ldap authorise: require group: "
                          "testing for group membership in \"%s\"",
                          getpid(), t);

            for (i = 0; i < sec->groupattr->nelts; i++) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "[%" APR_PID_T_FMT "] auth_ldap authorise: require group: "
                              "testing for %s: %s (%s)", getpid(),
                              ent[i].name, sec->group_attrib_is_dn ? req->dn : req->user, t);

                result = util_ldap_cache_compare(r, ldc, sec->url, t, ent[i].name,
                                     sec->group_attrib_is_dn ? req->dn : req->user);
                switch(result) {
                    case LDAP_COMPARE_TRUE: {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                      "[%" APR_PID_T_FMT "] auth_ldap authorise: require group: "
                                      "authorisation successful (attribute %s) [%s][%s]",
                                      getpid(), ent[i].name, ldc->reason, ldap_err2string(result));
                        return OK;
                    }
                    default: {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                      "[%" APR_PID_T_FMT "] auth_ldap authorise: require group \"%s\": "
                                      "authorisation failed [%s][%s]",
                                      getpid(), t, ldc->reason, ldap_err2string(result));
                    }
                }
            }
        }
        else if (strcmp(w, "ldap-attribute") == 0) {
            if (req->dn == NULL || strlen(req->dn) == 0) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                              "require ldap-attribute: user's DN has not been defined; failing authorisation",
                              getpid());
                return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
            }
            while (t[0]) {
                w = ap_getword(r->pool, &t, '=');
                value = ap_getword_conf(r->pool, &t);

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "[%" APR_PID_T_FMT "] auth_ldap authorise: checking attribute"
                              " %s has value %s", getpid(), w, value);
                result = util_ldap_cache_compare(r, ldc, sec->url, req->dn,
                                                 w, value);
                switch(result) {
                    case LDAP_COMPARE_TRUE: {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                      0, r, "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                      "require attribute: authorisation "
                                      "successful", getpid());
                        return OK;
                    }
                    default: {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                      0, r, "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                      "require attribute: authorisation "
                                      "failed [%s][%s]", getpid(),
                                      ldc->reason, ldap_err2string(result));
                    }
                }
            }
        }
        else if (strcmp(w, "ldap-filter") == 0) {
            if (req->dn == NULL || strlen(req->dn) == 0) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                              "require ldap-filter: user's DN has not been defined; failing authorisation",
                              getpid());
                return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
            }
            if (t[0]) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "[%" APR_PID_T_FMT "] auth_ldap authorise: checking filter %s",
                              getpid(), t);

                /* Build the username filter */
                authn_ldap_build_filter(filtbuf, r, req->user, t, sec);

                /* Search for the user DN */
                result = util_ldap_cache_getuserdn(r, ldc, sec->url, sec->basedn,
                     sec->scope, sec->attributes, filtbuf, &dn, &vals);

                /* Make sure that the filtered search returned the correct user dn */
                if (result == LDAP_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "[%" APR_PID_T_FMT "] auth_ldap authorise: checking dn match %s",
                                  getpid(), dn);
                    result = util_ldap_cache_comparedn(r, ldc, sec->url, req->dn, dn,
                         sec->compare_dn_on_server);
                }

                switch(result) {
                    case LDAP_COMPARE_TRUE: {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                      0, r, "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                      "require ldap-filter: authorisation "
                                      "successful", getpid());
                        return OK;
                    }
                    case LDAP_FILTER_ERROR: {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                      0, r, "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                      "require ldap-filter: %s authorisation "
                                      "failed [%s][%s]", getpid(),
                                      filtbuf, ldc->reason, ldap_err2string(result));
                        break;
                    }
                    default: {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                      0, r, "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                      "require ldap-filter: authorisation "
                                      "failed [%s][%s]", getpid(),
                                      ldc->reason, ldap_err2string(result));
                    }
                }
            }
        }
    }

    if (!method_restricted) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authorise: agreeing because non-restricted",
                      getpid());
        return OK;
    }

    if (!sec->auth_authoritative) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authorise: declining to authorise (not authoritative)", getpid());
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "[%" APR_PID_T_FMT "] auth_ldap authorise: authorisation denied", getpid());
    ap_note_basic_auth_failure (r);

    return HTTP_UNAUTHORIZED;
}


/*
 * Use the ldap url parsing routines to break up the ldap url into
 * host and port.
 */
static const char *mod_auth_ldap_parse_url(cmd_parms *cmd,
                                    void *config,
                                    const char *url,

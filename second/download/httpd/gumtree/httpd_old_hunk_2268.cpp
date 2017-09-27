        req->user = r->user;

    }

    if (req->dn == NULL || strlen(req->dn) == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authorize: "
                      "require user: user's DN has not been defined; failing authorization",
                      getpid());
        return AUTHZ_DENIED;
    }

    /*
     * First do a whole-line compare, in case it's something like
     *   require user Babs Jensen
     */
    result = util_ldap_cache_compare(r, ldc, sec->url, req->dn, sec->attribute, require_args);
    switch(result) {
        case LDAP_COMPARE_TRUE: {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "[%" APR_PID_T_FMT "] auth_ldap authorize: "
                          "require user: authorization successful", getpid());
            set_request_vars(r, LDAP_AUTHZ);
            return AUTHZ_GRANTED;
        }
        default: {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "[%" APR_PID_T_FMT "] auth_ldap authorize: require user: "
                          "authorization failed [%s][%s]", getpid(),
                          ldc->reason, ldap_err2string(result));
        }
    }

    /*
     * Now break apart the line and compare each word on it

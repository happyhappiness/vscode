        }
    }

    t = require_args;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "auth_ldap authorize: require group: testing for group "
                  "membership in \"%s\"",
                  t);

    for (i = 0; i < sec->groupattr->nelts; i++) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "auth_ldap authorize: require group: testing for %s: "
                      "%s (%s)",
                      ent[i].name,
                      sec->group_attrib_is_dn ? req->dn : req->user, t);

        result = util_ldap_cache_compare(r, ldc, sec->url, t, ent[i].name,
                             sec->group_attrib_is_dn ? req->dn : req->user);
        switch(result) {
            case LDAP_COMPARE_TRUE: {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
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

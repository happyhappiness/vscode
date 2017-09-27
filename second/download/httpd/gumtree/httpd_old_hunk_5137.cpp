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

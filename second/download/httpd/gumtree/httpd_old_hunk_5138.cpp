        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01742)
                      "auth_ldap authorize: require ldap-filter: user's DN "
                      "has not been defined; failing authorization");
        return AUTHZ_DENIED;
    }

    t = require_args;

    if (t[0]) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01743)
                      "auth_ldap authorize: checking filter %s", t);

        /* Build the username filter */

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

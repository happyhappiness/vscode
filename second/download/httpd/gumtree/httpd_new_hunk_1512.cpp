                 : (LDAP_INSUFFICIENT_ACCESS == result) ? AUTH_DENIED
#endif
#ifdef LDAP_INSUFFICIENT_RIGHTS
                 : (LDAP_INSUFFICIENT_RIGHTS == result) ? AUTH_DENIED
#endif
#endif
                 : AUTH_GENERAL_ERROR;
    }

    /* mark the user and DN */
    req->dn = apr_pstrdup(r->pool, dn);
    req->user = apr_pstrdup(r->pool, user);
    req->password = apr_pstrdup(r->pool, password);
    if (sec->user_is_dn) {
        r->user = req->dn;
    }

    /* add environment variables */
    remote_user_attribute_set = set_request_vars(r, LDAP_AUTHN);

    /* sanity check */
    if (sec->remote_user_attribute && !remote_user_attribute_set) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                  "[%" APR_PID_T_FMT "] auth_ldap authenticate: "
                  "REMOTE_USER was to be set with attribute '%s', "

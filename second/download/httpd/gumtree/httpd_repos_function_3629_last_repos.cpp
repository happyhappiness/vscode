static authn_status authn_ldap_check_password(request_rec *r, const char *user,
                                              const char *password)
{
    char filtbuf[FILTER_LENGTH];
    authn_ldap_config_t *sec =
        (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);

    util_ldap_connection_t *ldc = NULL;
    int result = 0;
    int remote_user_attribute_set = 0;
    const char *dn = NULL;
    const char *utfpassword;

    authn_ldap_request_t *req =
        (authn_ldap_request_t *)apr_pcalloc(r->pool, sizeof(authn_ldap_request_t));
    ap_set_module_config(r->request_config, &authnz_ldap_module, req);

/*
    if (!sec->enabled) {
        return AUTH_USER_NOT_FOUND;
    }
*/

    /*
     * Basic sanity checks before any LDAP operations even happen.
     */
    if (!sec->have_ldap_url) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02558) 
                      "no AuthLDAPURL");

        return AUTH_GENERAL_ERROR;
    }

    /* There is a good AuthLDAPURL, right? */
    if (sec->host) {
        const char *binddn = sec->binddn;
        const char *bindpw = sec->bindpw;
        if (sec->initial_bind_as_user) {
            bindpw = password;
            binddn = ldap_determine_binddn(r, user);
        }

        ldc = util_ldap_connection_find(r, sec->host, sec->port,
                                       binddn, bindpw,
                                       sec->deref, sec->secure);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01690)
                      "auth_ldap authenticate: no sec->host - weird...?");
        return AUTH_GENERAL_ERROR;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01691)
                  "auth_ldap authenticate: using URL %s", sec->url);

    /* Get the password that the client sent */
    if (password == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01692)
                      "auth_ldap authenticate: no password specified");
        util_ldap_connection_close(ldc);
        return AUTH_GENERAL_ERROR;
    }

    if (user == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01693)
                      "auth_ldap authenticate: no user specified");
        util_ldap_connection_close(ldc);
        return AUTH_GENERAL_ERROR;
    }

    /* build the username filter */
    authn_ldap_build_filter(filtbuf, r, user, NULL, sec);

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                      "auth_ldap authenticate: final authn filter is %s", filtbuf);

    /* convert password to utf-8 */
    utfpassword = authn_ldap_xlate_password(r, password);

    /* do the user search */
    result = util_ldap_cache_checkuserid(r, ldc, sec->url, sec->basedn, sec->scope,
                                         sec->attributes, filtbuf, utfpassword,
                                         &dn, &(req->vals));
    util_ldap_connection_close(ldc);

    /* handle bind failure */
    if (result != LDAP_SUCCESS) {
        if (!sec->bind_authoritative) {
           ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01694)
                      "auth_ldap authenticate: user %s authentication failed; "
                      "URI %s [%s][%s] (not authoritative)",
                      user, r->uri, ldc->reason, ldap_err2string(result));
           return AUTH_USER_NOT_FOUND;
        }

        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01695)
                      "auth_ldap authenticate: "
                      "user %s authentication failed; URI %s [%s][%s]",
                      user, r->uri, ldc->reason, ldap_err2string(result));

        /* talking to a primitive LDAP server (like RACF-over-LDAP) that doesn't return specific errors */
        if (!strcasecmp(sec->filter, "none") && LDAP_OTHER == result) { 
            return AUTH_USER_NOT_FOUND;
        }

        return (LDAP_NO_SUCH_OBJECT == result) ? AUTH_USER_NOT_FOUND
#ifdef LDAP_SECURITY_ERROR
                 : (LDAP_SECURITY_ERROR(result)) ? AUTH_DENIED
#else
                 : (LDAP_INAPPROPRIATE_AUTH == result) ? AUTH_DENIED
                 : (LDAP_INVALID_CREDENTIALS == result) ? AUTH_DENIED
#ifdef LDAP_INSUFFICIENT_ACCESS
                 : (LDAP_INSUFFICIENT_ACCESS == result) ? AUTH_DENIED
#endif
#ifdef LDAP_INSUFFICIENT_RIGHTS
                 : (LDAP_INSUFFICIENT_RIGHTS == result) ? AUTH_DENIED
#endif
#endif
#ifdef LDAP_CONSTRAINT_VIOLATION
    /* At least Sun Directory Server sends this if a user is
     * locked. This is not covered by LDAP_SECURITY_ERROR.
     */
                 : (LDAP_CONSTRAINT_VIOLATION == result) ? AUTH_DENIED
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
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01696)
                  "auth_ldap authenticate: "
                  "REMOTE_USER was to be set with attribute '%s', "
                  "but this attribute was not requested for in the "
                  "LDAP query for the user. REMOTE_USER will fall "
                  "back to username or DN as appropriate.",
                  sec->remote_user_attribute);
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01697)
                  "auth_ldap authenticate: accepting %s", user);

    return AUTH_GRANTED;
}
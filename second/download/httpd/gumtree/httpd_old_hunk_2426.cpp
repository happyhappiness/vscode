
        ldc = util_ldap_connection_find(r, sec->host, sec->port,
                                       binddn, bindpw,
                                       sec->deref, sec->secure);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                      "auth_ldap authenticate: no sec->host - weird...?");
        return AUTH_GENERAL_ERROR;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "auth_ldap authenticate: using URL %s", sec->url);

    /* Get the password that the client sent */
    if (password == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "auth_ldap authenticate: no password specified");
        util_ldap_connection_close(ldc);
        return AUTH_GENERAL_ERROR;
    }

    if (user == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "auth_ldap authenticate: no user specified");
        util_ldap_connection_close(ldc);
        return AUTH_GENERAL_ERROR;
    }

    /* build the username filter */
    authn_ldap_build_filter(filtbuf, r, user, NULL, sec);

    /* convert password to utf-8 */
    utfpassword = authn_ldap_xlate_password(r, password);

    /* do the user search */
    result = util_ldap_cache_checkuserid(r, ldc, sec->url, sec->basedn, sec->scope,
                                         sec->attributes, filtbuf, utfpassword,
                                         &dn, &(req->vals));
    util_ldap_connection_close(ldc);

    /* sanity check - if server is down, retry it up to 5 times */
    if (AP_LDAP_IS_SERVER_DOWN(result)) {
        if (failures++ <= 5) {
            goto start_over;
        }
    }

    /* handle bind failure */
    if (result != LDAP_SUCCESS) {
        if (!sec->bind_authoritative) {
           ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "auth_ldap authenticate: user %s authentication failed; "
                      "URI %s [%s][%s] (not authoritative)",
                      user, r->uri, ldc->reason, ldap_err2string(result));
           return AUTH_USER_NOT_FOUND;
        }

        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                      "auth_ldap authenticate: "
                      "user %s authentication failed; URI %s [%s][%s]",
                      user, r->uri, ldc->reason, ldap_err2string(result));

        return (LDAP_NO_SUCH_OBJECT == result) ? AUTH_USER_NOT_FOUND
#ifdef LDAP_SECURITY_ERROR

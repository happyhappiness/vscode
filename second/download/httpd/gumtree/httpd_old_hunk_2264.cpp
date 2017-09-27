        ldc = util_ldap_connection_find(r, sec->host, sec->port,
                                       binddn, bindpw,
                                       sec->deref, sec->secure);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authenticate: no sec->host - weird...?", getpid());
        return AUTH_GENERAL_ERROR;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "[%" APR_PID_T_FMT "] auth_ldap authenticate: using URL %s", getpid(), sec->url);

    /* Get the password that the client sent */
    if (password == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authenticate: no password specified", getpid());
        util_ldap_connection_close(ldc);
        return AUTH_GENERAL_ERROR;
    }

    if (user == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authenticate: no user specified", getpid());
        util_ldap_connection_close(ldc);
        return AUTH_GENERAL_ERROR;
    }

    /* build the username filter */
    authn_ldap_build_filter(filtbuf, r, user, NULL, sec);

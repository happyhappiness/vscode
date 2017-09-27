    }

start_over:

    /* There is a good AuthLDAPURL, right? */
    if (sec->host) {
        ldc = util_ldap_connection_find(r, sec->host, sec->port,
                                       sec->binddn, sec->bindpw, sec->deref,
                                       sec->secure);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authenticate: no sec->host - weird...?", getpid());
        return AUTH_GENERAL_ERROR;
    }

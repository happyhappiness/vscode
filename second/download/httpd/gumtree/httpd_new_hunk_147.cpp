        return DECLINED;
    }

    if (sec->host) {
        ldc = util_ldap_connection_find(r, sec->host, sec->port,
                                       sec->binddn, sec->bindpw, sec->deref,
                                       sec->secure);
        apr_pool_cleanup_register(r->pool, ldc,
                                  mod_auth_ldap_cleanup_connection_close,
                                  apr_pool_cleanup_null);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, r, 

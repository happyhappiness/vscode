
    /* do the user search */
    result = util_ldap_cache_checkuserid(r, ldc, sec->url, sec->basedn, sec->scope,
                                         sec->attributes, filtbuf, sent_pw, &dn, &vals);
    util_ldap_connection_close(ldc);

    /* sanity check - if server is down, retry it up to 5 times */
    if (result == LDAP_SERVER_DOWN) {
        util_ldap_connection_destroy(ldc);
        if (failures++ <= 5) {
            goto start_over;
        }
    }

    /* handle bind failure */
    if (result != LDAP_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, r, 
                      "[%d] auth_ldap authenticate: "
                      "user %s authentication failed; URI %s [%s][%s]",
		      getpid(), r->user, r->uri, ldc->reason, ldap_err2string(result));
        if ((LDAP_INVALID_CREDENTIALS == result) || sec->auth_authoritative) {
            ap_note_basic_auth_failure(r);
            return HTTP_UNAUTHORIZED;
        }
        else {
            return DECLINED;
        }
    }

    /* mark the user and DN */
    req->dn = apr_pstrdup(r->pool, dn);
    req->user = r->user;

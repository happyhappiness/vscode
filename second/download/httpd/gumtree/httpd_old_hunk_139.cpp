		      "[%d] auth_ldap authenticate: "
		      "ap_get_basic_auth_pw() returns %d", getpid(), result);
        util_ldap_connection_close(ldc);
        return result;
    }

    /* build the username filter */
    mod_auth_ldap_build_filter(filtbuf, r, sec);

    /* do the user search */
    result = util_ldap_cache_checkuserid(r, ldc, sec->url, sec->basedn, sec->scope,
                                         sec->attributes, filtbuf, sent_pw, &dn, &vals);

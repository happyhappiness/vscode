        rc = LDAP_TIMEOUT;
    } else if (ldap_parse_result(ldc->ldap, result, &rc, NULL, NULL, NULL,
                                 NULL, 1) == -1) {
        ldc->reason = "LDAP: ldap_simple_bind() parse result failed";
        return uldap_ld_errno(ldc);
    }
    return rc;
}

/*
 * Connect to the LDAP server and binds. Does not connect if already
 * connected (i.e. ldc->ldap is non-NULL.) Does not bind if already bound.

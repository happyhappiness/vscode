        else {
            ldc->reason = result->reason;
        }
        return(result->rc);
    }

    /* Now that we have an ldap struct, add it to the referral list for rebinds. */
    rc = apr_ldap_rebind_add(ldc->pool, ldc->ldap, ldc->binddn, ldc->bindpw);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "LDAP: Unable to add rebind cross reference entry. Out of memory?");
        uldap_connection_unbind(ldc);
        ldc->reason = "LDAP: Unable to add rebind cross reference entry.";
        return(rc);
    }

    /* always default to LDAP V3 */
    ldap_set_option(ldc->ldap, LDAP_OPT_PROTOCOL_VERSION, &version);

    /* set client certificates */
    if (!apr_is_empty_array(ldc->client_certs)) {
        apr_ldap_set_option(r->pool, ldc->ldap, APR_LDAP_OPT_TLS_CERT,
                            ldc->client_certs, &(result));
        if (LDAP_SUCCESS != result->rc) {
            uldap_connection_unbind( ldc );
            ldc->reason = result->reason;
            return(result->rc);
        }
    }

    /* switch on SSL/TLS */
    if (APR_LDAP_NONE != ldc->secure) {
        apr_ldap_set_option(r->pool, ldc->ldap,
                            APR_LDAP_OPT_TLS, &ldc->secure, &(result));
        if (LDAP_SUCCESS != result->rc) {
            uldap_connection_unbind( ldc );
            ldc->reason = result->reason;
            return(result->rc);

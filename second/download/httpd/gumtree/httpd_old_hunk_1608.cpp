        else {
            ldc->reason = result->reason;
        }
        return(result->rc);
    }

    /* always default to LDAP V3 */
    ldap_set_option(ldc->ldap, LDAP_OPT_PROTOCOL_VERSION, &version);

    /* set client certificates */
    if (!apr_is_empty_array(ldc->client_certs)) {
        apr_ldap_set_option(r->pool, ldc->ldap, APR_LDAP_OPT_TLS_CERT,

static int uldap_simple_bind(util_ldap_connection_t *ldc, char *binddn,
                             char* bindpw, struct timeval *timeout)
{
    LDAPMessage *result;
    int rc;
    int msgid = ldap_simple_bind(ldc->ldap, binddn, bindpw);
    if (msgid == -1) {
        ldc->reason = "LDAP: ldap_simple_bind() failed";
        /* -1 is LDAP_SERVER_DOWN in openldap, use something else */
        return LDAP_OTHER;
    }
    rc = ldap_result(ldc->ldap, msgid, 0, timeout, &result);
    if (rc == -1) {
        ldc->reason = "LDAP: ldap_simple_bind() result retrieval failed";
        /* -1 is LDAP_SERVER_DOWN in openldap, use something else */
        rc = LDAP_OTHER;
    }
    else if (rc == 0) {
        ldc->reason = "LDAP: ldap_simple_bind() timed out";
        rc = LDAP_TIMEOUT;
    } else if (ldap_parse_result(ldc->ldap, result, &rc, NULL, NULL, NULL,
                                 NULL, 1) == -1) {
        ldc->reason = "LDAP: ldap_simple_bind() parse result failed";
    }
    return rc;
}
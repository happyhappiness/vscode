static int
ldap_simple_rebind(LDAP * ld,
                   LDAP_CONST char *url, ber_tag_t request, ber_int_t msgid, void *params)
{
    struct ldap_creds *cp = (struct ldap_creds *) params;
    struct berval cred;
    if (cp->pw) {
        cred.bv_val = cp->pw;
        cred.bv_len = strlen(cp->pw);
    }
    return ldap_sasl_bind_s(ld, cp->dn, LDAP_SASL_SIMPLE, &cred, NULL, NULL,
                            NULL);
}
static int
ldap_simple_rebind(
    LDAP * ld,
    LDAP_CONST char *url,
    ber_tag_t request,
    ber_int_t msgid,
    void *params)
{

    struct ldap_creds *cp = (struct ldap_creds *) params;
    return ldap_bind_s(ld, cp->dn, cp->pw, LDAP_AUTH_SIMPLE);
}
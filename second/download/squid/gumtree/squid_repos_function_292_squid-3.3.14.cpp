static int
ldap_sasl_rebind(
    LDAP * ld,
    LDAP_CONST char *url,
    ber_tag_t request,
    ber_int_t msgid,
    void *params)
{
    struct ldap_creds *cp = (struct ldap_creds *) params;
    return tool_sasl_bind(ld, cp->dn, cp->pw);
}
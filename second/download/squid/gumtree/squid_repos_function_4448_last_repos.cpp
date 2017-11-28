static int LDAP_CALL LDAP_CALLBACK
ldap_sasl_rebind(LDAP * ld,
                 char **whop, char **credp, int *methodp, int freeit, void *params)
{
    struct ldap_creds *cp = (struct ldap_creds *) params;
    whop = whop;
    credp = credp;
    methodp = methodp;
    freeit = freeit;
    return tool_sasl_bind(ld, cp->dn, cp->pw);
}
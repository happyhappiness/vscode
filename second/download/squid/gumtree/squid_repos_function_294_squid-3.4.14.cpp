static int
ldap_simple_rebind(
    LDAP * ld,
    char **whop,
    char **credp,
    int *methodp,
    int freeit,
    void *params)
{
    struct ldap_creds *cp = (struct ldap_creds *) params;
    whop = whop;
    credp = credp;
    methodp = methodp;
    freeit = freeit;
    return ldap_bind_s(ld, cp->dn, cp->pw, LDAP_AUTH_SIMPLE);
}
static int
ldap_simple_rebind(LDAP * ld,
                   char **whop, char **credp, int *methodp, int freeit, void *params)
{
    struct ldap_creds *cp = (struct ldap_creds *) params;
    struct berval cred;
    if (cp->pw) {
        cred.bv_val = cp->pw;
        cred.bv_len = strlen(cp->pw);
    }
    whop = whop;
    credp = credp;
    methodp = methodp;
    freeit = freeit;
    return ldap_sasl_bind_s(ld, cp->dn, LDAP_SASL_SIMPLE, &cred, NULL, NULL,
                            NULL);
}
int ldap_search_ext_s(LDAP *ldap, char *base, int scope, char *filter,
		      char **attrs, int attrsonly, void *servertrls, void *clientctrls,
		      void *timeout, int sizelimit, LDAPMessage **res)
{
    return ldap_search_s(ldap, base, scope, filter, attrs, attrsonly, res);
}
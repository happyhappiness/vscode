static void
squid_ldap_set_aliasderef(int deref)
{
    ldap_set_option(ld, LDAP_OPT_DEREF, &deref);
}
static void
squid_ldap_set_timelimit(LDAP * ld, int aTimeLimit)
{
    ldap_set_option(ld, LDAP_OPT_TIMELIMIT, &aTimeLimit);
}
static void
squid_ldap_set_referrals(LDAP * ld, int referrals)
{
    int *value = static_cast<int*>(referrals ? LDAP_OPT_ON :LDAP_OPT_OFF);
    ldap_set_option(ld, LDAP_OPT_REFERRALS, value);
}
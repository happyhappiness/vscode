static void
squid_ldap_set_referrals(LDAP * ld, int referrals)
{
    if (referrals)
        ld->ld_options |= ~LDAP_OPT_REFERRALS;
    else
        ld->ld_options &= ~LDAP_OPT_REFERRALS;
}
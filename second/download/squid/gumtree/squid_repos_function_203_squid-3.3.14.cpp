static void
squid_ldap_set_timelimit(LDAP * ld, int timelimit)
{
    ld->ld_timelimit = timelimit;
}
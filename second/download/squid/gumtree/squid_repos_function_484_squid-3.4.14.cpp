static int
squid_ldap_errno(LDAP * ld)
{
    return ld->ld_errno;
}
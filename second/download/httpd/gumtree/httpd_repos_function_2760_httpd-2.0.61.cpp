static int ldap_pvt_unhex(int c)
{
    return( c >= '0' && c <= '9' ? c - '0'
        : c >= 'A' && c <= 'F' ? c - 'A' + 10
        : c - 'a' + 10 );
}
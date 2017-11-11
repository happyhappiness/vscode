static int str2scope(const char *p)
{
    if ( strcasecmp( p, "one" ) == 0 ) {
        return LDAP_SCOPE_ONELEVEL;

    } else if ( strcasecmp( p, "onetree" ) == 0 ) {
        return LDAP_SCOPE_ONELEVEL;

    } else if ( strcasecmp( p, "base" ) == 0 ) {
        return LDAP_SCOPE_BASE;

    } else if ( strcasecmp( p, "sub" ) == 0 ) {
        return LDAP_SCOPE_SUBTREE;

    } else if ( strcasecmp( p, "subtree" ) == 0 ) {
        return LDAP_SCOPE_SUBTREE;
    }

    return( -1 );
}
static void ldap_pvt_hex_unescape(char *s)
{
    /*
     * Remove URL hex escapes from s... done in place.  The basic concept for
     * this routine is borrowed from the WWW library HTUnEscape() routine.
     */
    char    *p;

    for ( p = s; *s != '\0'; ++s ) {
        if ( *s == '%' ) {
            if ( *++s == '\0' ) {
                break;
            }
            *p = ldap_pvt_unhex( *s ) << 4;
            if ( *++s == '\0' ) {
                break;
            }
            *p++ += ldap_pvt_unhex( *s );
        } else {
            *p++ = *s;
        }
    }

    *p = '\0';
}
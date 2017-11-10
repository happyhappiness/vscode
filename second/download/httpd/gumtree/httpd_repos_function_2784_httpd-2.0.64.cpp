static const char *skip_url_prefix(const char *url, int *enclosedp,
                                   const char **scheme)
{
    /*
     * return non-zero if this looks like a LDAP URL; zero if not
     * if non-zero returned, *urlp will be moved past "ldap://" part of URL
     */
    const char *p;

    if ( url == NULL ) {
        return( NULL );
    }

    p = url;

    /* skip leading '<' (if any) */
    if ( *p == '<' ) {
        *enclosedp = 1;
        ++p;
    } else {
        *enclosedp = 0;
    }

    /* skip leading "URL:" (if any) */
    if ( strncasecmp( p, LDAP_URL_URLCOLON, LDAP_URL_URLCOLON_LEN ) == 0 ) {
        p += LDAP_URL_URLCOLON_LEN;
    }

    /* check for "ldap://" prefix */
    if ( strncasecmp( p, LDAP_URL_PREFIX, LDAP_URL_PREFIX_LEN ) == 0 ) {
        /* skip over "ldap://" prefix and return success */
        p += LDAP_URL_PREFIX_LEN;
        *scheme = "ldap";
        return( p );
    }

    /* check for "ldaps://" prefix */
    if ( strncasecmp( p, LDAPS_URL_PREFIX, LDAPS_URL_PREFIX_LEN ) == 0 ) {
        /* skip over "ldaps://" prefix and return success */
        p += LDAPS_URL_PREFIX_LEN;
        *scheme = "ldaps";
        return( p );
    }

    /* check for "ldapi://" prefix */
    if ( strncasecmp( p, LDAPI_URL_PREFIX, LDAPI_URL_PREFIX_LEN ) == 0 ) {
        /* skip over "ldapi://" prefix and return success */
        p += LDAPI_URL_PREFIX_LEN;
        *scheme = "ldapi";
        return( p );
    }

    return( NULL );
}
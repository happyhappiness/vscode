static char **ldap_str2charray(const char *str_in, const char *brkstr)
{
    char    **res;
    char    *str, *s;
    char    *lasts;
    int i;

    /* protect the input string from strtok */
    str = LDAP_STRDUP( str_in );
    if( str == NULL ) {
        return NULL;
    }

    i = 1;
    for ( s = str; *s; s++ ) {
        if ( ldap_utf8_strchr( brkstr, s ) != NULL ) {
            i++;
        }
    }

    res = (char **) LDAP_MALLOC( (i + 1) * sizeof(char *) );

    if( res == NULL ) {
        LDAP_FREE( str );
        return NULL;
    }

    i = 0;

    for ( s = ldap_utf8_strtok( str, brkstr, &lasts );
        s != NULL;
        s = ldap_utf8_strtok( NULL, brkstr, &lasts ) )
    {
        res[i] = LDAP_STRDUP( s );

        if(res[i] == NULL) {
            for( --i ; i >= 0 ; i-- ) {
                LDAP_FREE( res[i] );
            }
            LDAP_FREE( res );
            LDAP_FREE( str );
            return NULL;
        }

        i++;
    }

    res[i] = NULL;

    LDAP_FREE( str );
    return( res );
}
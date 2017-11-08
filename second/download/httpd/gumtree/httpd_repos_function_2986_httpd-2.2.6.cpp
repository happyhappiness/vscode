static char **apr_ldap_str2charray(apr_pool_t *pool,
                                   const char *str_in,
                                   const char *brkstr)
{
    char    **res;
    char    *str, *s;
    char    *lasts;
    int i;

    /* protect the input string from strtok */
    str = (char *)apr_pstrdup(pool, str_in);
    if( str == NULL ) {
        return NULL;
    }

    i = 1;
    for ( s = str; *s; s++ ) {
        /* Warning: this strchr was previously ldap_utf8_strchr(), check
         * whether this particular code has any charset issues.
         */
        if ( strchr( brkstr, *s ) != NULL ) {
            i++;
        }
    }

    res = (char **) apr_pcalloc(pool, (i + 1) * sizeof(char *));
    if( res == NULL ) {
        return NULL;
    }

    i = 0;

    for ( s = (char *)apr_strtok( str, brkstr, &lasts );
          s != NULL;
          s = (char *)apr_strtok( NULL, brkstr, &lasts ) ) {

        res[i] = (char *)apr_pstrdup(pool, s);
        if(res[i] == NULL) {
            return NULL;
        }

        i++;
    }

    res[i] = NULL;

    return( res );

}
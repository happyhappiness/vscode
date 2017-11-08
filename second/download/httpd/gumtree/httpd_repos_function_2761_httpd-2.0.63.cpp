static void ldap_charray_free(char **a)
{
    char    **p;

    if ( a == NULL ) {
        return;
    }

    for ( p = a; *p != NULL; p++ ) {
        if ( *p != NULL ) {
            LDAP_FREE( *p );
        }
    }

    LDAP_FREE( (char *) a );
}
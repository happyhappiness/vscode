bool
REList::match( const char* check ) const
{
    int result = regexec( &rexp, check, 0, 0, 0 );
    if ( result != 0 && result != REG_NOMATCH ) {
        char buffer[256];
        regerror( result, &rexp, buffer, 256 );
        fprintf( stderr, "unable to execute re \"%s\"\n+ on line \"%s\": %s\n",
                 data, check, buffer );
        exit(1);
    }
    return ( result == 0 );
}
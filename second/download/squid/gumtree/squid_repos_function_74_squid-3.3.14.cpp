char*
concat( const char* start, ... )
// purpose: concatinate an arbitrary number of C strings.
// paramtr: start (IN): first C string
//          ... (IN): further C strings, terminated with a NULL pointer
// returns: memory allocated via new(), containing the concatinated string.
{
    va_list ap;
    const char* s;

    // first run: determine size
    unsigned size = strlen(start)+1;
    va_start( ap, start );
    while ( (s=va_arg(ap,const char*)) != NULL ) size += strlen(s ? s : "");
    va_end(ap);

    // allocate
    char* result = new char[size];
    if ( result == 0 ) {
        perror( "string memory allocation" );
        exit(1);
    }

    // second run: copy content
    strcpy( result, start );
    va_start( ap, start );
    while ( (s=va_arg(ap,const char*)) != NULL ) strcat( result, s );
    va_end(ap);

    return result;
}
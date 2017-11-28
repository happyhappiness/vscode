int
checkForPortOnly( const char* arg )
// purpose: see if somebody just put in a port instead of a hostname
// paramtr: optarg (IN): argument from commandline
// returns: 0..65535 is the valid port number in network byte order,
//          -1 if not a port
{
    // if there is a period in there, it must be a valid hostname
    if ( strchr( arg, '.' ) != 0 ) return -1;

    // if it is just a number between 0 and 65535, it must be a port
    char* errstr = 0;
    unsigned long result = strtoul( arg, &errstr, 0 );
    if ( result < 65536 && errstr != arg ) return htons(result);

#if 0
    // one last try, test for a symbolical service name
    struct servent* service = getservbyname( arg, "tcp" );
    return service ? service->s_port : -1;
#else
    return -1;
#endif
}
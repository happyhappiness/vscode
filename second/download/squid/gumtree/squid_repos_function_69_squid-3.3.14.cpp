int
convertPortname( const char* port, unsigned short& dst )
// purpose: convert a numeric or symbolic port number
// paramtr: port (IN): port description to convert
//          dst (OUT): port number in network byteorder.
// returns: -1 in case of error, see errno; 0 otherwise.
{
    int p = strtoul(port,0,0);

    if ( p == 0 ) {
        // symbolic port
        struct servent* proto = getservbyname( port, "tcp" );
        if ( proto == NULL ) return -1;
        else dst = proto->s_port;
    } else {
        // numeric port
        dst = htons(p);
    }
    return 0;
}
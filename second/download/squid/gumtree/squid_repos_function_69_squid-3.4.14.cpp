int
convertHostname( const char* host, in_addr& dst )
// purpose: convert a numeric or symbolic hostname
// paramtr: host (IN): host description to convert
//          dst (OUT): the internet address in network byteorder.
// returns: -1 in case of error, see h_errno; 0 otherwise.
{
    if ( host == 0 ) return -1;
    unsigned long int h = inet_addr(host);
    if ( h == 0xFFFFFFFF && strncmp(host,"255.255.255.255",15) != 0 ) {
        // symbolic host
        struct hostent* dns = gethostbyname(host);
        if ( dns == NULL ) return -1;
        else memcpy( &dst.s_addr, dns->h_addr, dns->h_length );
    } else {
        // numeric host
        dst.s_addr = h;
    }
    return 0;
}
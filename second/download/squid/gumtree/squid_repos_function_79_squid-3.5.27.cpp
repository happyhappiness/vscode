const char*
my_inet_ntoa( const struct in_addr& a, HostAddress output )
// purpose: thread-safely convert IPv4 address -> ASCII representation
// paramtr: a (IN): networked representation of IPv4 address
//          buffer (OUT): storage area to store representation into.
// returns: pointer to buffer
// goodies: INADDR_ANY will be converted to "*"
{
    if ( a.s_addr == ntohl(INADDR_ANY) ) {
        // 'default' or '*' or ...
        output[0] = '*';
        output[1] = '\0';
    } else {
        // ANSI C++ forbids casting to an array type, nag, nag, nag...
        unsigned char s[sizeof(a.s_addr)];
        memcpy( s, &a.s_addr, sizeof(a.s_addr) );

        snprintf(output, sizeof(HostAddress), "%d.%d.%d.%d", s[0], s[1], s[2], s[3] );
    }
    return output;
}
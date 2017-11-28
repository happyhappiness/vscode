const char*
my_sock_ntoa( const struct sockaddr_in& a, SockAddress buffer )
// purpose: thread-safely convert IPv4 socket pair into ASCII rep.
// paramtr: a (IN): sockaddr_in address
//          buffer (OUT): storage area to store representation into.
// returns: pointer to buffer
{
    HostAddress host;
    snprintf( buffer, sizeof(SockAddress), "%s:%u",
              my_inet_ntoa(a.sin_addr,host), ntohs(a.sin_port) );
    return buffer;
}
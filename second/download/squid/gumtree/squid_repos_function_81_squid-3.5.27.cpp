const char*
my_sock_fd2a( int fd, SockAddress buffer, bool peer )
// purpose: thread-safely convert IPv4 socket FD associated address
//          to ASCII representation
// paramtr: fd (IN): open socket FD
//          buffer (OUT): storage area
//          peer (IN): true, use peer (remote) socket pair
//                     false, use own (local) socket pair
// returns: NULL in case of error, or pointer to buffer otherwise
//          Refer to errno in case of error (usually unconnected fd...)
{
    struct sockaddr_in socket;
    socklen_t len = sizeof(socket);

    if ( (peer ? getpeername( fd, (SA*) &socket, &len ) :
            getsockname( fd, (SA*) &socket, &len )) == -1 )
        return NULL;
    else
        return my_sock_ntoa( socket, buffer );
}
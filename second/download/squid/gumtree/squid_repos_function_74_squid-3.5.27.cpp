int
getSocketNoDelay( int sockfd )
// purpose: get state of the TCP_NODELAY of the socket
// paramtr: sockfd (IN): socket descriptor
// returns: 1, if TCP_NODELAY is set,
//          0, if TCP_NODELAY is not set,
//         -1, if an error occurred (e.g. datagram socket)
{
    int delay = 0;
    socklen_t len = sizeof(delay);
    if ( getsockopt( sockfd, IPPROTO_TCP, TCP_NODELAY,
                     (char*) &delay, &len ) == -1 ) {
        perror( "# getsockopt( TCP_NODELAY ) failed" );
        return -1;
    } else
        return ( delay ? 1 : 0 );
}
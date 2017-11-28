int
setSocketNoDelay( int sockfd, bool)
// purpose: get state of the TCP_NODELAY of the socket
// paramtr: sockfd (IN): socket descriptor
//          nodelay (IN): true, if TCP_NODELAY is to be set, false otherwise.
// returns: 0, if everything worked out o.k.
//         -1, if an error occurred (e.g. datagram socket)
{
    const int delay = 1;
    if ( setsockopt( sockfd, IPPROTO_TCP, TCP_NODELAY,
                     (const char*) &delay, sizeof(delay) ) == -1 ) {
        perror( "setsockopt( TCP_NODELAY ) failed" );
        return -1;
    } else
        return 0;
}
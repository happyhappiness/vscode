int
commonCode( int& sockfd, bool nodelay, int sendBufferSize, int recvBufferSize )
// purpose: common code in server sockets and client sockets
// paramtr: sockfd (IO): socket filedescriptor
//          nodelay (IN): true=set TCP_NODELAY option.
//          sendBufferSize (IN): don't set (use sys defaults) if < 0
//          recvBufferSize (IN): don't set (use sys defaults) if < 0
// returns: 0 == if everthing went ok, -1 otherwise
// warning: sockfd will be closed, if -1 is returned!
{
    // set TCP_NODELAY option, if that is wanted.
    // The socket API default is unset.
    if ( nodelay ) {
        const int delay = 1;
        if ( setsockopt( sockfd, IPPROTO_TCP, TCP_NODELAY,
                         (const char*) &delay, sizeof(delay) ) == -1 ) {
            perror( "setsockopt( TCP_NODELAY ) failed" );
            close(sockfd);
            return -1;
        }
    }

    // set the socket send buffer size explicitly, or use the system default
    if ( sendBufferSize >= 0 ) {
        if ( setsockopt( sockfd, SOL_SOCKET, SO_SNDBUF, (char*) &sendBufferSize,
                         sizeof(sendBufferSize) ) == -1 ) {
            perror( "setsockopt( SO_SNDBUF )" );
            close(sockfd);
            return -1;
        }
    }

    // set the socket recv buffer size explicitly, or use the system default
    if ( recvBufferSize >= 0 ) {
        if ( setsockopt( sockfd, SOL_SOCKET, SO_RCVBUF, (char*) &recvBufferSize,
                         sizeof(recvBufferSize) ) == -1 ) {
            perror( "setsockopt( SO_RCVBUF )" );
            close(sockfd);
            return -1;
        }
    }
    return 0;
}
int
setSocketBuffers( int sockfd, int size )
// purpose: set socket buffers for both directions to the specified size
// paramtr: sockfd (IN): socket file descriptor
//          size (IN): new socket buffer size
// returns: -1 on setsockopt() errors, 0 otherwise
// warning: prints error message on stderr, errno will be changed
{
    if ( setsockopt( sockfd, SOL_SOCKET, SO_RCVBUF,
                     (char*) &size, sizeof(size) ) == -1 ) {
        perror( "setsockopt( SO_RCVBUF )" );
        return -1;
    }

    if ( setsockopt( sockfd, SOL_SOCKET, SO_SNDBUF,
                     (char*) &size, sizeof(size) ) == -1 ) {
        perror( "setsockopt( SO_SNDBUF )" );
        return -1;
    }

    return 0;
}
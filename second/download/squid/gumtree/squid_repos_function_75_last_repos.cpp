int
serverSocket( struct in_addr host, unsigned short port,
              int backlog, bool reuse, bool nodelay,
              int sendBufferSize, int recvBufferSize )
// purpose: open a server socket for listening
// paramtr: host (IN): host to bind locally to, use INADDRY_ANY for *
//          port (IN): port to bind to, use 0 for system assigned
//          backlog (IN): listen backlog queue length
//          reuse (IN): set SO_REUSEADDR option - default usefully
//          nodelay (IN): true=set TCP_NODELAY option.
//            SETTING TCP_NODELAY ON A SERVER SOCKET DOES NOT MAKE SENSE!
//          sendBufferSize (IN): don't set (use sys defaults) if < 0
//          recvBufferSize (IN): don't set (use sys defaults) if < 0
// returns: opened listening fd, or -1 on error.
// warning: error message will be printed on stderr and errno reset.
{
    int sockfd = socket( AF_INET, SOCK_STREAM, 0 );
    if ( sockfd == -1 ) {
        perror( "socket" );
        return -1;
    }

    if ( reuse ) {
        int opt = 1;
        if ( setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR,
                         (char*) &opt, sizeof(int) ) == -1) {
            perror( "setsockopt( SO_REUSEADDR )" );
            close( sockfd );
            return -1;
        }
    }

    if ( commonCode( sockfd, nodelay, sendBufferSize, recvBufferSize ) == -1 )
        return -1;

    struct sockaddr_in server;
    memset( &server, 0, sizeof(server) );
    server.sin_family = AF_INET;
    server.sin_port   = port;
    server.sin_addr   = host;
    if ( bind( sockfd, (SA*) &server, sizeof(server) ) == -1 ) {
        SockAddress socket;
        fprintf( stderr, "bind(%s): %s\n",
                 my_sock_ntoa(server,socket), strerror(errno) );
        close(sockfd);
        return -1;
    }

    if ( listen( sockfd, backlog ) == -1 ) {
        perror( "listen" );
        close(sockfd);
        return -1;
    }

    return sockfd;
}
int
connectTo( struct in_addr host, unsigned short port, bool nodelay,
           int sendBufferSize, int recvBufferSize )
// purpose: connect to a server as a client
// paramtr: host (IN): address describing the server
//          port (IN): port to connect at the server
//          nodelay (IN): true=set TCP_NODELAY option.
//          sendBufferSize (IN): don't set (use sys defaults) if < 0
//          recvBufferSize (IN): don't set (use sys defaults) if < 0
// returns: >=0 is the descriptor of the opened, connected socket,
//          -1  is an indication of an error (errno may have been reset).
{
    int sockfd = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( sockfd == -1 ) {
        perror( "socket() failed" );
        return -1;
    }

    if ( commonCode( sockfd, nodelay, sendBufferSize, recvBufferSize ) == -1 )
        return -1;

    struct sockaddr_in server;
    memset( &server, 0, sizeof(server) );
    server.sin_family = AF_INET;
    server.sin_addr   = host;
    server.sin_port   = port;
    if ( connect( sockfd, (struct sockaddr*) &server, sizeof(server) ) == -1 ) {
        perror( "connect() failure" );
        close(sockfd);
        return -1;
    }

    return sockfd;
}
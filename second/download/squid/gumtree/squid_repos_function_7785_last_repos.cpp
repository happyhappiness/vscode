int
RFCNB_IP_Connect(struct in_addr Dest_IP, int port)
{
    struct sockaddr_in Socket;
    int fd;

    /* Create a socket */

    if ((fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {   /* Handle the error */

        RFCNB_errno = RFCNBE_BadSocket;
        RFCNB_saved_errno = errno;
        return (RFCNBE_Bad);
    }
    memset((char *) &Socket, 0, sizeof(Socket));
    memcpy((char *) &Socket.sin_addr, (char *) &Dest_IP, sizeof(Dest_IP));

    Socket.sin_port = htons(port);
    Socket.sin_family = PF_INET;

    /* Now connect to the destination */

    if (connect(fd, (struct sockaddr *) &Socket, sizeof(Socket)) < 0) {         /* Error */

        close(fd);
        RFCNB_errno = RFCNBE_ConnectFailed;
        RFCNB_saved_errno = errno;
        return (RFCNBE_Bad);
    }
    return (fd);
}
int
comm_open_listener(int sock_type,
                   int proto,
                   Ip::Address &addr,
                   int flags,
                   const char *note)
{
    int sock = -1;

    /* all listener sockets require bind() */
    flags |= COMM_DOBIND;

    /* attempt native enabled port. */
    sock = comm_openex(sock_type, proto, addr, flags, 0, 0, note);

    return sock;
}
void
comm_open_listener(int sock_type,
                   int proto,
                   Comm::ConnectionPointer &conn,
                   const char *note)
{
    /* all listener sockets require bind() */
    conn->flags |= COMM_DOBIND;

    /* attempt native enabled port. */
    conn->fd = comm_openex(sock_type, proto, conn->local, conn->flags, 0, 0, note);
}
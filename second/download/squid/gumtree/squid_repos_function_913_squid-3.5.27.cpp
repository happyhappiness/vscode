void
comm_reset_close(const Comm::ConnectionPointer &conn)
{
    struct linger L;
    L.l_onoff = 1;
    L.l_linger = 0;

    if (setsockopt(conn->fd, SOL_SOCKET, SO_LINGER, (char *) &L, sizeof(L)) < 0)
        debugs(50, DBG_CRITICAL, "ERROR: Closing " << conn << " with TCP RST: " << xstrerror());

    conn->close();
}
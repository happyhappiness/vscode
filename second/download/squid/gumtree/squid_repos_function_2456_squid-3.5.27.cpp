static void
idnsSentQueryVC(const Comm::ConnectionPointer &conn, char *buf, size_t size, Comm::Flag flag, int xerrno, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (flag == Comm::ERR_CLOSING)
        return;

    // XXX: irrelevant now that we have conn pointer?
    if (!Comm::IsConnOpen(conn) || fd_table[conn->fd].closing())
        return;

    if (flag != Comm::OK || size <= 0) {
        conn->close();
        return;
    }

    vc->busy = 0;
    idnsDoSendQueryVC(vc);
}
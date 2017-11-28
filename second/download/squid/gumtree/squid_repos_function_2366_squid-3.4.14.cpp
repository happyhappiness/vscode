static void
idnsSentQueryVC(const Comm::ConnectionPointer &conn, char *buf, size_t size, comm_err_t flag, int xerrno, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (flag == COMM_ERR_CLOSING)
        return;

    // XXX: irrelevant now that we have conn pointer?
    if (!Comm::IsConnOpen(conn) || fd_table[conn->fd].closing())
        return;

    if (flag != COMM_OK || size <= 0) {
        conn->close();
        return;
    }

    vc->busy = 0;
    idnsDoSendQueryVC(vc);
}
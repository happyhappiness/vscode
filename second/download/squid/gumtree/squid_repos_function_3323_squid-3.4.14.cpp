void
IdleConnList::Read(const Comm::ConnectionPointer &conn, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    debugs(48, 3, HERE << len << " bytes from " << conn);

    if (flag == COMM_ERR_CLOSING) {
        debugs(48, 3, HERE << "COMM_ERR_CLOSING from " << conn);
        /* Bail out on COMM_ERR_CLOSING - may happen when shutdown aborts our idle FD */
        return;
    }

    IdleConnList *list = (IdleConnList *) data;
    /* may delete list/data */
    list->findAndClose(conn);
}
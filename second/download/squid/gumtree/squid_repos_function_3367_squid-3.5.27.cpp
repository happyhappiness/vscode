void
IdleConnList::Read(const Comm::ConnectionPointer &conn, char *buf, size_t len, Comm::Flag flag, int xerrno, void *data)
{
    debugs(48, 3, HERE << len << " bytes from " << conn);

    if (flag == Comm::ERR_CLOSING) {
        debugs(48, 3, HERE << "Comm::ERR_CLOSING from " << conn);
        /* Bail out on Comm::ERR_CLOSING - may happen when shutdown aborts our idle FD */
        return;
    }

    IdleConnList *list = (IdleConnList *) data;
    /* may delete list/data */
    list->findAndClose(conn);
}
void
IdleConnList::Timeout(const CommTimeoutCbParams &io)
{
    debugs(48, 3, HERE << io.conn);
    IdleConnList *list = static_cast<IdleConnList *>(io.data);
    /* may delete list/data */
    list->findAndClose(io.conn);
}
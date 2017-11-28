DeferredRead
DeferredReadManager::popHead(CbDataListContainer<DeferredRead> &deferredReads)
{
    assert (!deferredReads.empty());

    DeferredRead &read = deferredReads.head->element;

    // NOTE: at this point the connection has been paused/stalled for an unknown
    //       amount of time. We must re-validate that it is active and usable.

    // If the connection has been closed already. Cancel this read.
    if (!fd_table || !Comm::IsConnOpen(read.theRead.conn)) {
        if (read.closer != NULL) {
            read.closer->cancel("Connection closed before.");
            read.closer = NULL;
        }
        read.markCancelled();
    }

    if (!read.cancelled) {
        comm_remove_close_handler(read.theRead.conn->fd, read.closer);
        read.closer = NULL;
    }

    DeferredRead result = deferredReads.pop_front();

    return result;
}
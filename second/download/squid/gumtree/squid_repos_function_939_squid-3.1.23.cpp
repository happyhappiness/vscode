DeferredRead
DeferredReadManager::popHead(CbDataListContainer<DeferredRead> &deferredReads)
{
    assert (!deferredReads.empty());

    DeferredRead &read = deferredReads.head->element;
    if (!read.cancelled) {
        comm_remove_close_handler(read.theRead.fd, read.closer);
        read.closer = NULL;
    }

    DeferredRead result = deferredReads.pop_front();

    return result;
}
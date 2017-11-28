void
DeferredReadManager::delayRead(DeferredRead const &aRead)
{
    debugs(5, 3, "Adding deferred read on " << aRead.theRead.conn);
    CbDataList<DeferredRead> *temp = deferredReads.push_back(aRead);

    // We have to use a global function as a closer and point to temp
    // instead of "this" because DeferredReadManager is not a job and
    // is not even cbdata protected
    // XXX: and yet we use cbdata protection functions on it??
    AsyncCall::Pointer closer = commCbCall(5,4,
                                           "DeferredReadManager::CloseHandler",
                                           CommCloseCbPtrFun(&CloseHandler, temp));
    comm_add_close_handler(aRead.theRead.conn->fd, closer);
    temp->element.closer = closer; // remeber so that we can cancel
}
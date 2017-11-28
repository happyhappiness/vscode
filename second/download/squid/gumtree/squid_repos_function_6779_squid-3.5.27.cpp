void
Ipc::JoinSharedListen(const OpenListenerParams &params, AsyncCall::Pointer &cb)
{
    PendingOpenRequest por;
    por.params = params;
    por.callback = cb;

    const DelayedSharedListenRequests::size_type concurrencyLimit = 1;
    if (TheSharedListenRequestMap.size() >= concurrencyLimit) {
        debugs(54, 3, "waiting for " << TheSharedListenRequestMap.size() <<
               " active + " << TheDelayedRequests.size() << " delayed requests");
        TheDelayedRequests.push_back(por);
    } else {
        SendSharedListenRequest(por);
    }
}
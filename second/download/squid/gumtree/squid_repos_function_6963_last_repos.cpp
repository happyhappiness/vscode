void
Ipc::Coordinator::handleCacheMgrRequest(const Mgr::Request& request)
{
    debugs(54, 4, HERE);

    try {
        Mgr::Action::Pointer action =
            CacheManager::GetInstance()->createRequestedAction(request.params);
        AsyncJob::Start(new Mgr::Inquirer(action, request, strands_));
    } catch (const std::exception &ex) {
        debugs(54, DBG_IMPORTANT, "BUG: cannot aggregate mgr:" <<
               request.params.actionName << ": " << ex.what());
        // TODO: Avoid half-baked Connections or teach them how to close.
        ::close(request.conn->fd);
        request.conn->fd = -1;
        return; // the worker will timeout and close
    }

    // Let the strand know that we are now responsible for handling the request
    Mgr::Response response(request.requestId);
    TypedMsgHdr message;
    response.pack(message);
    SendMessage(MakeAddr(strandAddrLabel, request.requestorId), message);

}
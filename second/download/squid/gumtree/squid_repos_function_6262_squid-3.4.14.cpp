void Ipc::JoinSharedListen(const OpenListenerParams &params,
                           AsyncCall::Pointer &callback)
{
    PendingOpenRequest por;
    por.params = params;
    por.callback = callback;

    SharedListenRequest request;
    request.requestorId = KidIdentifier;
    request.params = por.params;
    request.mapId = AddToMap(por);

    debugs(54, 3, HERE << "getting listening FD for " << request.params.addr <<
           " mapId=" << request.mapId);

    TypedMsgHdr message;
    request.pack(message);
    SendMessage(coordinatorAddr, message);
}
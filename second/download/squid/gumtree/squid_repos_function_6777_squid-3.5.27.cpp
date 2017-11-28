static void
SendSharedListenRequest(const PendingOpenRequest &por)
{
    Ipc::SharedListenRequest request;
    request.requestorId = KidIdentifier;
    request.params = por.params;
    request.mapId = AddToMap(por);

    debugs(54, 3, "getting listening FD for " << request.params.addr <<
           " mapId=" << request.mapId);

    Ipc::TypedMsgHdr message;
    request.pack(message);
    SendMessage(Ipc::Port::CoordinatorAddr(), message);
}
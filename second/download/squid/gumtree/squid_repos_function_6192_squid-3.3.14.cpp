void
Ipc::Coordinator::handleSharedListenRequest(const SharedListenRequest& request)
{
    debugs(54, 4, HERE << "kid" << request.requestorId <<
           " needs shared listen FD for " << request.params.addr);
    Listeners::const_iterator i = listeners.find(request.params);
    int errNo = 0;
    const Comm::ConnectionPointer c = (i != listeners.end()) ?
                                      i->second : openListenSocket(request, errNo);

    debugs(54, 3, HERE << "sending shared listen " << c << " for " <<
           request.params.addr << " to kid" << request.requestorId <<
           " mapId=" << request.mapId);

    SharedListenResponse response(c->fd, errNo, request.mapId);
    TypedMsgHdr message;
    response.pack(message);
    SendMessage(MakeAddr(strandAddrPfx, request.requestorId), message);
}
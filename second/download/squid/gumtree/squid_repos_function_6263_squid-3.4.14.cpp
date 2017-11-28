void Ipc::SharedListenJoined(const SharedListenResponse &response)
{
    // Dont debugs c fully since only FD is filled right now.
    debugs(54, 3, HERE << "got listening FD " << response.fd << " errNo=" <<
           response.errNo << " mapId=" << response.mapId);

    Must(TheSharedListenRequestMap.find(response.mapId) != TheSharedListenRequestMap.end());
    PendingOpenRequest por = TheSharedListenRequestMap[response.mapId];
    Must(por.callback != NULL);
    TheSharedListenRequestMap.erase(response.mapId);

    StartListeningCb *cbd = dynamic_cast<StartListeningCb*>(por.callback->getDialer());
    assert(cbd && cbd->conn != NULL);
    Must(cbd && cbd->conn != NULL);
    cbd->conn->fd = response.fd;

    if (Comm::IsConnOpen(cbd->conn)) {
        OpenListenerParams &p = por.params;
        cbd->conn->local = p.addr;
        cbd->conn->flags = p.flags;
        // XXX: leave the comm AI stuff to comm_import_opened()?
        struct addrinfo *AI = NULL;
        p.addr.getAddrInfo(AI);
        AI->ai_socktype = p.sock_type;
        AI->ai_protocol = p.proto;
        comm_import_opened(cbd->conn, FdNote(p.fdNote), AI);
        Ip::Address::FreeAddrInfo(AI);
    }

    cbd->errNo = response.errNo;
    cbd->handlerSubscription = por.params.handlerSubscription;
    ScheduleCallHere(por.callback);
}
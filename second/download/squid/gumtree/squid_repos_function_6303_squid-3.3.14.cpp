void
Ipc::Inquirer::inquire()
{
    if (pos == strands.end()) {
        Must(done());
        return;
    }

    Must(request->requestId == 0);
    AsyncCall::Pointer callback = asyncCall(54, 5, "Mgr::Inquirer::handleRemoteAck",
                                            HandleAckDialer(this, &Inquirer::handleRemoteAck, NULL));
    if (++LastRequestId == 0) // don't use zero value as request->requestId
        ++LastRequestId;
    request->requestId = LastRequestId;
    const int kidId = pos->kidId;
    debugs(54, 4, HERE << "inquire kid: " << kidId << status());
    TheRequestsMap[request->requestId] = callback;
    TypedMsgHdr message;
    request->pack(message);
    SendMessage(Port::MakeAddr(strandAddrPfx, kidId), message);
    eventAdd("Ipc::Inquirer::requestTimedOut", &Inquirer::RequestTimedOut,
             this, timeout, 0, false);
}
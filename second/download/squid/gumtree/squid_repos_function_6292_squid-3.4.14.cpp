void
Ipc::Forwarder::start()
{
    debugs(54, 3, HERE);

    typedef NullaryMemFunT<Forwarder> Dialer;
    AsyncCall::Pointer callback = JobCallback(54, 5, Dialer, this, Forwarder::handleRemoteAck);
    if (++LastRequestId == 0) // don't use zero value as request->requestId
        ++LastRequestId;
    request->requestId = LastRequestId;
    TheRequestsMap[request->requestId] = callback;
    TypedMsgHdr message;

    try {
        request->pack(message);
    } catch (...) {
        // assume the pack() call failed because the message did not fit
        // TODO: add a more specific exception?
        handleError();
    }

    SendMessage(coordinatorAddr, message);
    eventAdd("Ipc::Forwarder::requestTimedOut", &Forwarder::RequestTimedOut,
             this, timeout, 0, false);
}
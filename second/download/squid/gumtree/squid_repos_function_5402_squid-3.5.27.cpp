void
Ftp::Relay::forwardPreliminaryReply(const PreliminaryCb cb)
{
    debugs(9, 5, "forwarding preliminary reply to client");

    // we must prevent concurrent ConnStateData::sendControlMsg() calls
    Must(thePreliminaryCb == NULL);
    thePreliminaryCb = cb;

    const HttpReply::Pointer reply = createHttpReply(Http::scContinue);

    // the Sink will use this to call us back after writing 1xx to the client
    typedef NullaryMemFunT<Relay> CbDialer;
    const AsyncCall::Pointer call = JobCallback(11, 3, CbDialer, this,
                                    Ftp::Relay::proceedAfterPreliminaryReply);

    CallJobHere1(9, 4, request->clientConnectionManager, ConnStateData,
                 ConnStateData::sendControlMsg, HttpControlMsg(reply, call));
}
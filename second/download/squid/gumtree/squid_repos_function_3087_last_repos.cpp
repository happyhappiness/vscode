void
ConnStateData::doneWithControlMsg()
{
    HttpControlMsgSink::doneWithControlMsg();

    if (Http::StreamPointer deferredRequest = pipeline.front()) {
        debugs(33, 3, clientConnection << ": calling PushDeferredIfNeeded after control msg wrote");
        ClientSocketContextPushDeferredIfNeeded(deferredRequest, this);
    }
}
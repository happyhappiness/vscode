void
TunnelStateData::startConnecting()
{
    Comm::ConnectionPointer &dest = serverDestinations.front();
    GetMarkingsToServer(request.getRaw(), *dest);

    const time_t connectTimeout = dest->connectTimeout(startTime);
    AsyncCall::Pointer call = commCbCall(26,3, "tunnelConnectDone", CommConnectCbPtrFun(tunnelConnectDone, this));
    Comm::ConnOpener *cs = new Comm::ConnOpener(dest, call, connectTimeout);
    cs->setHost(url);
    AsyncJob::Start(cs);
}
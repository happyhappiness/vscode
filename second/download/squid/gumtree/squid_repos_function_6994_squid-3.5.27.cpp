void Ipc::Port::doListen()
{
    debugs(54, 6, HERE);
    buf.prepForReading();
    typedef CommCbMemFunT<Port, CommIoCbParams> Dialer;
    AsyncCall::Pointer readHandler = JobCallback(54, 6,
                                     Dialer, this, Port::noteRead);
    comm_read(conn(), buf.raw(), buf.size(), readHandler);
}
void Ipc::UdsSender::write()
{
    debugs(54, 5, HERE);
    typedef CommCbMemFunT<UdsSender, CommIoCbParams> Dialer;
    AsyncCall::Pointer writeHandler = JobCallback(54, 5,
                                      Dialer, this, UdsSender::wrote);
    Comm::Write(conn(), message.raw(), message.size(), writeHandler, NULL);
    writing = true;
}
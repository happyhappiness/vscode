void
Mgr::StoreToCommWriter::scheduleCommWrite(const StoreIOBuffer& ioBuf)
{
    debugs(16, 6, HERE);
    Must(Comm::IsConnOpen(clientConnection));
    Must(ioBuf.data != NULL);
    // write filled buffer
    typedef CommCbMemFunT<StoreToCommWriter, CommIoCbParams> MyDialer;
    AsyncCall::Pointer writer =
        asyncCall(16, 5, "Mgr::StoreToCommWriter::noteCommWrote",
                  MyDialer(this, &StoreToCommWriter::noteCommWrote));
    Comm::Write(clientConnection, ioBuf.data, ioBuf.length, writer, NULL);
}
void
TunnelStateData::readConnectResponse()
{
    assert(waitingForConnectResponse());

    AsyncCall::Pointer call = commCbCall(5,4, "readConnectResponseDone",
                                         CommIoCbPtrFun(ReadConnectResponseDone, this));
    comm_read(server.conn, connectRespBuf->space(),
              server.bytesWanted(1, connectRespBuf->spaceSize()), call);
}
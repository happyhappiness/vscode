void
TunnelStateData::copyRead(Connection &from, IOCB *completion)
{
    assert(from.len == 0);
    AsyncCall::Pointer call = commCbCall(5,4, "TunnelBlindCopyReadHandler",
                                         CommIoCbPtrFun(completion, this));
    comm_read(from.conn, from.buf, from.bytesWanted(1, SQUID_TCP_SO_RCVBUF), call);
}
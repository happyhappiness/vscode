void
TunnelStateData::copyRead(Connection &from, IOCB *completion)
{
    assert(from.len == 0);
    // If only the minimum permitted read size is going to be attempted
    // then we schedule an event to try again in a few I/O cycles.
    // Allow at least 1 byte to be read every (0.3*10) seconds.
    int bw = from.bytesWanted(1, SQUID_TCP_SO_RCVBUF);
    if (bw == 1 && ++from.delayedLoops < 10) {
        from.readPending = this;
        eventAdd("tunnelDelayedServerRead", from.readPendingFunc, from.readPending, 0.3, true);
        return;
    }

    AsyncCall::Pointer call = commCbCall(5,4, "TunnelBlindCopyReadHandler",
                                         CommIoCbPtrFun(completion, this));
    comm_read(from.conn, from.buf, bw, call);
}
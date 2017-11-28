void
TunnelStateData::copyRead(Connection &from, IOCB *completion)
{
    assert(from.len == 0);
    comm_read(from.fd(), from.buf, from.bytesWanted(1, SQUID_TCP_SO_RCVBUF), completion, this);
}
void
TunnelStateData::copyServerBytes()
{
    if (preReadServerData.length()) {
        size_t copyBytes = preReadServerData.length() > SQUID_TCP_SO_RCVBUF ? SQUID_TCP_SO_RCVBUF : preReadServerData.length();
        memcpy(server.buf, preReadServerData.rawContent(), copyBytes);
        preReadServerData.consume(copyBytes);
        server.bytesIn(copyBytes);
        if (keepGoingAfterRead(copyBytes, Comm::OK, 0, server, client))
            copy(copyBytes, server, client, TunnelStateData::WriteClientDone);
    } else
        copyRead(server, ReadServer);
}
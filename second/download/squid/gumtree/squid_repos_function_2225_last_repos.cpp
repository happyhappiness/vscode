void
TunnelStateData::copyClientBytes()
{
    if (preReadClientData.length()) {
        size_t copyBytes = preReadClientData.length() > SQUID_TCP_SO_RCVBUF ? SQUID_TCP_SO_RCVBUF : preReadClientData.length();
        memcpy(client.buf, preReadClientData.rawContent(), copyBytes);
        preReadClientData.consume(copyBytes);
        client.bytesIn(copyBytes);
        if (keepGoingAfterRead(copyBytes, Comm::OK, 0, client, server))
            copy(copyBytes, client, server, TunnelStateData::WriteServerDone);
    } else
        copyRead(client, ReadClient);
}
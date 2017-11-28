void
ConnStateData::clientPinnedConnectionRead(const CommIoCbParams &io)
{
    pinning.readHandler = NULL; // Comm unregisters handlers before calling

    if (io.flag == COMM_ERR_CLOSING)
        return; // close handler will clean up

    // We could use getConcurrentRequestCount(), but this may be faster.
    const bool clientIsIdle = !getCurrentContext();

    debugs(33, 3, "idle pinned " << pinning.serverConnection << " read " <<
           io.size << (clientIsIdle ? " with idle client" : ""));

    assert(pinning.serverConnection == io.conn);
    pinning.serverConnection->close();

    // If we are still sending data to the client, do not close now. When we are done sending,
    // ClientSocketContext::keepaliveNextRequest() checks pinning.serverConnection and will close.
    // However, if we are idle, then we must close to inform the idle client and minimize races.
    if (clientIsIdle && clientConnection != NULL)
        clientConnection->close();
}
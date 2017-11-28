void
ConnStateData::clientPinnedConnectionRead(const CommIoCbParams &io)
{
    pinning.readHandler = NULL; // Comm unregisters handlers before calling

    if (io.flag == Comm::ERR_CLOSING)
        return; // close handler will clean up

    Must(pinning.serverConnection == io.conn);

#if USE_OPENSSL
    if (handleIdleClientPinnedTlsRead())
        return;
#endif

    const bool clientIsIdle = pipeline.empty();

    debugs(33, 3, "idle pinned " << pinning.serverConnection << " read " <<
           io.size << (clientIsIdle ? " with idle client" : ""));

    pinning.serverConnection->close();

    // If we are still sending data to the client, do not close now. When we are done sending,
    // ConnStateData::kick() checks pinning.serverConnection and will close.
    // However, if we are idle, then we must close to inform the idle client and minimize races.
    if (clientIsIdle && clientConnection != NULL)
        clientConnection->close();
}
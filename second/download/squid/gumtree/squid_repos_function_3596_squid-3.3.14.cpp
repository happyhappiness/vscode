void
ConnStateData::clientPinnedConnectionClosed(const CommCloseCbParams &io)
{
    // FwdState might repin a failed connection sooner than this close
    // callback is called for the failed connection.
    assert(pinning.serverConnection == io.conn);
    pinning.closeHandler = NULL; // Comm unregisters handlers before calling
    const bool sawZeroReply = pinning.zeroReply; // reset when unpinning
    unpinConnection();
    if (sawZeroReply && clientConnection != NULL) {
        debugs(33, 3, "Closing client connection on pinned zero reply.");
        clientConnection->close();
    }
}
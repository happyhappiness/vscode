void
ConnStateData::notePinnedConnectionBecameIdle(PinnedIdleContext pic)
{
    Must(pic.connection != NULL);
    Must(pic.request != NULL);
    pinConnection(pic.connection, pic.request);

    // monitor pinned server connection for remote-end closures.
    startPinnedConnectionMonitoring();

    if (!currentobject)
        kick(); // in case clientParseRequests() was blocked by a busy pic.connection
}
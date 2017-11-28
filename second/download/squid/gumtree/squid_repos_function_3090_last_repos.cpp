void
ConnStateData::notePinnedConnectionBecameIdle(PinnedIdleContext pic)
{
    Must(pic.connection);
    Must(pic.request);
    pinConnection(pic.connection, *pic.request);

    // monitor pinned server connection for remote-end closures.
    startPinnedConnectionMonitoring();

    if (pipeline.empty())
        kick(); // in case clientParseRequests() was blocked by a busy pic.connection
}
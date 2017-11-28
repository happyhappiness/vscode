void
ConnStateData::endingShutdown()
{
    // RegisteredRunner API callback - Squid shutdown grace period is over

    // force the client connection to close immediately
    // swanSong() in the close handler will cleanup.
    if (Comm::IsConnOpen(clientConnection))
        clientConnection->close();

    // deregister now to ensure finalShutdown() does not kill us prematurely.
    // fd_table purge will cleanup if close handler was not fast enough.
    DeregisterRunner(this);
}
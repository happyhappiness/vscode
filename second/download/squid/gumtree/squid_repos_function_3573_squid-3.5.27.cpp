void
ConnStateData::swanSong()
{
    debugs(33, 2, HERE << clientConnection);
    flags.readMore = false;
    DeregisterRunner(this);
    clientdbEstablished(clientConnection->remote, -1);  /* decrement */
    assert(areAllContextsForThisConnection());
    freeAllContexts();

    // XXX: Closing pinned conn is too harsh: The Client may want to continue!
    unpinConnection(true);

    if (Comm::IsConnOpen(clientConnection))
        clientConnection->close();

#if USE_AUTH
    // NP: do this bit after closing the connections to avoid side effects from unwanted TCP RST
    setAuth(NULL, "ConnStateData::SwanSong cleanup");
#endif

    BodyProducer::swanSong();
    flags.swanSang = true;
}
/* This is a handler normally called by comm_close() */
void ConnStateData::connStateClosed(const CommCloseCbParams &io)
{
    deleteThis("ConnStateData::connStateClosed");
}

// cleans up before destructor is called
void
ConnStateData::swanSong()
{
    debugs(33, 2, HERE << clientConnection);
    flags.readMore = false;
    clientdbEstablished(clientConnection->remote, -1);	/* decrement */
    assert(areAllContextsForThisConnection());
    freeAllContexts();
#if USE_AUTH
    if (auth_user_request != NULL) {
        debugs(33, 4, "ConnStateData::swanSong: freeing auth_user_request '" << auth_user_request << "' (this is '" << this << "')");
        auth_user_request->onConnectionClose(this);
    }
#endif

    unpinConnection();

    if (Comm::IsConnOpen(clientConnection))
        clientConnection->close();
    clientConnection = NULL;

    BodyProducer::swanSong();
    flags.swanSang = true;
}

bool

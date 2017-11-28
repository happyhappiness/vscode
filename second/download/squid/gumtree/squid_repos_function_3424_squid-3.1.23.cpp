void
ConnStateData::swanSong()
{
    debugs(33, 2, "ConnStateData::swanSong: FD " << fd);
    fd = -1;
    flags.readMoreRequests = false;
    clientdbEstablished(peer, -1);	/* decrement */
    assert(areAllContextsForThisConnection());
    freeAllContexts();

    if (auth_user_request != NULL) {
        debugs(33, 4, "ConnStateData::swanSong: freeing auth_user_request '" << auth_user_request << "' (this is '" << this << "')");
        auth_user_request->onConnectionClose(this);
    }

    if (pinning.fd >= 0)
        comm_close(pinning.fd);

    BodyProducer::swanSong();
    flags.swanSang = true;
}
void
PeerPoolMgr::start()
{
    AsyncJob::start();

    const MasterXaction::Pointer mx = new MasterXaction(XactionInitiator::initPeerPool);
    // ErrorState, getOutgoingAddress(), and other APIs may require a request.
    // We fake one. TODO: Optionally send this request to peers?
    request = new HttpRequest(Http::METHOD_OPTIONS, AnyP::PROTO_HTTP, "http", "*", mx);
    request->url.host(peer->host);

    checkpoint("peer initialized");
}
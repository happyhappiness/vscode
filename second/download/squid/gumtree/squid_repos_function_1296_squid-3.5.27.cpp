void
PeerPoolMgr::start()
{
    AsyncJob::start();

    // ErrorState, getOutgoingAddress(), and other APIs may require a request.
    // We fake one. TODO: Optionally send this request to peers?
    request = new HttpRequest(Http::METHOD_OPTIONS, AnyP::PROTO_HTTP, "*");
    request->SetHost(peer->host);

    checkpoint("peer initialized");
}
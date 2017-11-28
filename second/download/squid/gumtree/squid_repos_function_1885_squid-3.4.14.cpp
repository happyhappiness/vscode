void
peerConnectFailed(CachePeer *p)
{
    debugs(15, DBG_IMPORTANT, "TCP connection to " << p->host << "/" << p->http_port << " failed");
    peerConnectFailedSilent(p);
}
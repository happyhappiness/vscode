void
peerConnectFailed(peer *p)
{
    debugs(15, 1, "TCP connection to " << p->host << "/" << p->http_port << " failed");
    peerConnectFailedSilent(p);
}
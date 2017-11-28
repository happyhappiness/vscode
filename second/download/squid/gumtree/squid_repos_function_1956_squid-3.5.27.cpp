bool
peerHasConnAvailable(const CachePeer *p)
{
    // Standby connections can be used without opening new connections.
    const int standbys = p->standby.pool ? p->standby.pool->count() : 0;

    // XXX: Some idle pconns can be used without opening new connections.
    // Complication: Idle pconns cannot be reused for some requests.
    const int usableIdles = 0;

    const int available = standbys + usableIdles;
    debugs(15, 7, available << '=' << standbys << '+' << usableIdles);
    return available > 0;
}
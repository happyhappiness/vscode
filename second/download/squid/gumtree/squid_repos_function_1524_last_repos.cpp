int
neighborsCount(HttpRequest * request)
{
    CachePeer *p = NULL;
    int count = 0;

    for (p = Config.peers; p; p = p->next)
        if (peerWouldBePinged(p, request))
            ++count;

    debugs(15, 3, "neighborsCount: " << count);

    return count;
}
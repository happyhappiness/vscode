static int
peerSortWeight(const void *a, const void *b)
{
    const CachePeer *const *p1 = (const CachePeer *const *)a;
    const CachePeer *const *p2 = (const CachePeer *const *)b;
    return (*p1)->weight - (*p2)->weight;
}
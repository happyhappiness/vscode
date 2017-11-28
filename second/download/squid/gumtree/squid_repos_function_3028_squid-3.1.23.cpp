static int
peerSortWeight(const void *a, const void *b)
{
    const peer *const *p1 = (const peer *const *)a;
    const peer *const *p2 = (const peer *const *)b;
    return (*p1)->weight - (*p2)->weight;
}
void
PconnPool::closeN(int n, const Comm::ConnectionPointer &destLink, const char *domain)
{
    // TODO: optimize: we can probably do hash_lookup just once
    for (int i = 0; i < n; ++i)
        pop(destLink, domain, false); // may fail!
}
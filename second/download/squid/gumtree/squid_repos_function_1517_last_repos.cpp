peer_t
neighborType(const CachePeer * p, const URL &url)
{

    const NeighborTypeDomainList *d = NULL;

    for (d = p->typelist; d; d = d->next) {
        if (0 == matchDomainName(url.host(), d->domain))
            if (d->type != PEER_NONE)
                return d->type;
    }
#if PEER_MULTICAST_SIBLINGS
    if (p->type == PEER_MULTICAST)
        if (p->options.mcast_siblings)
            return PEER_SIBLING;
#endif

    return p->type;
}
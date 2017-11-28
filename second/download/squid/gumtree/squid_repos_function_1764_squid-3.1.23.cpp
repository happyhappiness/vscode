peer_t
neighborType(const peer * p, const HttpRequest * request)
{

    const struct _domain_type *d = NULL;

    for (d = p->typelist; d; d = d->next) {
        if (0 == matchDomainName(request->GetHost(), d->domain))
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
int
peerAllowedToUse(const peer * p, HttpRequest * request)
{

    const struct _domain_ping *d = NULL;
    int do_ping = 1;
    assert(request != NULL);

    if (neighborType(p, request) == PEER_SIBLING) {
#if PEER_MULTICAST_SIBLINGS
        if (p->type == PEER_MULTICAST && p->options.mcast_siblings &&
                (request->flags.nocache || request->flags.refresh || request->flags.loopdetect || request->flags.need_validation))
            debugs(15, 2, "peerAllowedToUse(" << p->name << ", " << request->GetHost() << ") : multicast-siblings optimization match");
#endif
        if (request->flags.nocache)
            return 0;

        if (request->flags.refresh)
            return 0;

        if (request->flags.loopdetect)
            return 0;

        if (request->flags.need_validation)
            return 0;
    }

    // CONNECT requests are proxy requests. Not to be forwarded to origin servers.
    // Unless the destination port matches, in which case we MAY perform a 'DIRECT' to this peer.
    if (p->options.originserver && request->method == METHOD_CONNECT && request->port != p->in_addr.GetPort())
        return 0;

    if (p->peer_domain == NULL && p->access == NULL)
        return do_ping;

    do_ping = 0;

    for (d = p->peer_domain; d; d = d->next) {
        if (0 == matchDomainName(request->GetHost(), d->domain)) {
            do_ping = d->do_ping;
            break;
        }

        do_ping = !d->do_ping;
    }

    if (p->peer_domain && 0 == do_ping)
        return do_ping;

    if (p->access == NULL)
        return do_ping;

    ACLFilledChecklist checklist(p->access, request, NULL);
    checklist.src_addr = request->client_addr;
    checklist.my_addr = request->my_addr;

#if 0 && USE_IDENT
    /*
     * this is currently broken because 'request->user_ident' has been
     * moved to conn->rfc931 and we don't have access to the parent
     * ConnStateData here.
     */
    if (request->user_ident[0])
        xstrncpy(checklist.rfc931, request->user_ident, USER_IDENT_SZ);

#endif

    return checklist.fastCheck();
}
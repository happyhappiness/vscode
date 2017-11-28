void
neighborsHtcpReply(const cache_key * key, HtcpReplyData * htcp, const Ip::Address &from)
{
    StoreEntry *e = Store::Root().get(key);
    MemObject *mem = NULL;
    CachePeer *p;
    peer_t ntype = PEER_NONE;
    debugs(15, 6, "neighborsHtcpReply: " <<
           (htcp->hit ? "HIT" : "MISS") << " " <<
           storeKeyText(key)  );

    if (NULL != e)
        mem = e->mem_obj;

    if ((p = whichPeer(from)))
        neighborAliveHtcp(p, mem, htcp);

    /* Does the entry exist? */
    if (NULL == e) {
        debugs(12, 3, "neighyborsHtcpReply: Cache key '" << storeKeyText(key) << "' not found");
        neighborCountIgnored(p);
        return;
    }

    /* check if someone is already fetching it */
    if (EBIT_TEST(e->flags, ENTRY_DISPATCHED)) {
        debugs(15, 3, "neighborsUdpAck: '" << storeKeyText(key) << "' already being fetched.");
        neighborCountIgnored(p);
        return;
    }

    if (mem == NULL) {
        debugs(15, 2, "Ignoring reply for missing mem_obj: " << storeKeyText(key));
        neighborCountIgnored(p);
        return;
    }

    if (e->ping_status != PING_WAITING) {
        debugs(15, 2, "neighborsUdpAck: Entry " << storeKeyText(key) << " is not PING_WAITING");
        neighborCountIgnored(p);
        return;
    }

    if (e->lock_count == 0) {
        // TODO: many entries are unlocked; why is this reported at level 1?
        debugs(12, DBG_IMPORTANT, "neighborsUdpAck: '" << storeKeyText(key) << "' has no locks");
        neighborCountIgnored(p);
        return;
    }

    if (p) {
        ntype = neighborType(p, mem->request);
        neighborUpdateRtt(p, mem);
    }

    if (ignoreMulticastReply(p, mem)) {
        neighborCountIgnored(p);
        return;
    }

    debugs(15, 3, "neighborsHtcpReply: e = " << e);
    mem->ping_reply_callback(p, ntype, AnyP::PROTO_HTCP, htcp, mem->ircb_data);
}
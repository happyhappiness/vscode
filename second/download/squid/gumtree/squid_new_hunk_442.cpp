        storeAppendPrintf(sentry, "keep-alive ratio: %d%%\n", Math::intPercent(e->stats.n_keepalives_recv, e->stats.n_keepalives_sent));
    }
}

#if USE_HTCP
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

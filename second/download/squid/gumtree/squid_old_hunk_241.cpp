        storeAppendPrintf(sentry, "keep-alive ratio: %d%%\n", Math::intPercent(e->stats.n_keepalives_recv, e->stats.n_keepalives_sent));
    }
}

#if USE_HTCP
void
neighborsHtcpReply(const cache_key * key, htcpReplyData * htcp, const IpAddress &from)
{
    StoreEntry *e = Store::Root().get(key);
    MemObject *mem = NULL;
    peer *p;
    peer_t ntype = PEER_NONE;
    debugs(15, 6, "neighborsHtcpReply: " <<

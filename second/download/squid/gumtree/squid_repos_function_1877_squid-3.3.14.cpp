static void
peerCountMcastPeersStart(void *data)
{
    CachePeer *p = (CachePeer *)data;
    ps_state *psstate;
    StoreEntry *fake;
    MemObject *mem;
    icp_common_t *query;
    int reqnum;
    LOCAL_ARRAY(char, url, MAX_URL);
    assert(p->type == PEER_MULTICAST);
    p->mcast.flags.count_event_pending = 0;
    snprintf(url, MAX_URL, "http://");
    p->in_addr.ToURL(url+7, MAX_URL -8 );
    strcat(url, "/");
    fake = storeCreateEntry(url, url, RequestFlags(), METHOD_GET);
    HttpRequest *req = HttpRequest::CreateFromUrl(url);
    psstate = new ps_state;
    psstate->request = HTTPMSGLOCK(req);
    psstate->entry = fake;
    psstate->callback = NULL;
    psstate->callback_data = cbdataReference(p);
    psstate->ping.start = current_time;
    mem = fake->mem_obj;
    mem->request = HTTPMSGLOCK(psstate->request);
    mem->start_ping = current_time;
    mem->ping_reply_callback = peerCountHandleIcpReply;
    mem->ircb_data = psstate;
    mcastSetTtl(icpOutgoingConn->fd, p->mcast.ttl);
    p->mcast.id = mem->id;
    reqnum = icpSetCacheKey((const cache_key *)fake->key);
    query = _icp_common_t::createMessage(ICP_QUERY, 0, url, reqnum, 0);
    icpUdpSend(icpOutgoingConn->fd, p->in_addr, query, LOG_ICP_QUERY, 0);
    fake->ping_status = PING_WAITING;
    eventAdd("peerCountMcastPeersDone",
             peerCountMcastPeersDone,
             psstate,
             Config.Timeout.mcast_icp_query / 1000.0, 1);
    p->mcast.flags.counting = 1;
    peerCountMcastPeersSchedule(p, MCAST_COUNT_RATE);
}
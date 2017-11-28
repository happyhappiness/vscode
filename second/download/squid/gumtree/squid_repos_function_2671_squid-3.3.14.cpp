static void

htcpHandleTstResponse(htcpDataHeader * hdr, char *buf, int sz, Ip::Address &from)
{
    HtcpReplyData htcpReply;
    cache_key *key = NULL;

    Ip::Address *peer;
    htcpDetail *d = NULL;
    char *t;

    if (queried_id[hdr->msg_id % N_QUERIED_KEYS] != hdr->msg_id) {
        debugs(31, 2, "htcpHandleTstResponse: No matching query id '" <<
               hdr->msg_id << "' (expected " <<
               queried_id[hdr->msg_id % N_QUERIED_KEYS] << ") from '" <<
               from << "'");

        return;
    }

    key = queried_keys[hdr->msg_id % N_QUERIED_KEYS];

    if (!key) {
        debugs(31, 3, "htcpHandleTstResponse: No query key for response id '" << hdr->msg_id << "' from '" << from << "'");
        return;
    }

    peer = &queried_addr[hdr->msg_id % N_QUERIED_KEYS];

    if ( *peer != from || peer->GetPort() != from.GetPort() ) {
        debugs(31, 3, "htcpHandleTstResponse: Unexpected response source " << from );
        return;
    }

    if (hdr->F1 == 1) {
        debugs(31, 2, "htcpHandleTstResponse: error condition, F1/MO == 1");
        return;
    }

    htcpReply.msg_id = hdr->msg_id;
    debugs(31, 3, "htcpHandleTstResponse: msg_id = " << htcpReply.msg_id);
    htcpReply.hit = hdr->response ? 0 : 1;

    if (hdr->F1) {
        debugs(31, 3, "htcpHandleTstResponse: MISS");
    } else {
        debugs(31, 3, "htcpHandleTstResponse: HIT");
        d = htcpUnpackDetail(buf, sz);

        if (d == NULL) {
            debugs(31, 3, "htcpHandleTstResponse: bad DETAIL");
            return;
        }

        if ((t = d->resp_hdrs))
            htcpReply.hdr.parse(t, t + strlen(t));

        if ((t = d->entity_hdrs))
            htcpReply.hdr.parse(t, t + strlen(t));

        if ((t = d->cache_hdrs))
            htcpReply.hdr.parse(t, t + strlen(t));
    }

    debugs(31, 3, "htcpHandleTstResponse: key (" << key << ") " << storeKeyText(key));
    neighborsHtcpReply(key, &htcpReply, from);
    htcpReply.hdr.clean();

    if (d)
        htcpFreeDetail(d);
}
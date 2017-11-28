void

neighborsUdpAck(const cache_key * key, icp_common_t * header, const IpAddress &from)
{
    peer *p = NULL;
    StoreEntry *entry;
    MemObject *mem = NULL;
    peer_t ntype = PEER_NONE;
    char *opcode_d;
    icp_opcode opcode = (icp_opcode) header->opcode;

    debugs(15, 6, "neighborsUdpAck: opcode " << opcode << " '" << storeKeyText(key) << "'");

    if (NULL != (entry = Store::Root().get(key)))
        mem = entry->mem_obj;

    if ((p = whichPeer(from)))
        neighborAlive(p, mem, header);

    if (opcode > ICP_END)
        return;

    opcode_d = icp_opcode_str[opcode];

    if (p)
        neighborUpdateRtt(p, mem);

    /* Does the entry exist? */
    if (NULL == entry) {
        debugs(12, 3, "neighborsUdpAck: Cache key '" << storeKeyText(key) << "' not found");
        neighborCountIgnored(p);
        return;
    }

    /* check if someone is already fetching it */
    if (EBIT_TEST(entry->flags, ENTRY_DISPATCHED)) {
        debugs(15, 3, "neighborsUdpAck: '" << storeKeyText(key) << "' already being fetched.");
        neighborCountIgnored(p);
        return;
    }

    if (mem == NULL) {
        debugs(15, 2, "Ignoring " << opcode_d << " for missing mem_obj: " << storeKeyText(key));
        neighborCountIgnored(p);
        return;
    }

    if (entry->ping_status != PING_WAITING) {
        debugs(15, 2, "neighborsUdpAck: Late " << opcode_d << " for " << storeKeyText(key));
        neighborCountIgnored(p);
        return;
    }

    if (entry->lock_count == 0) {
        debugs(12, 1, "neighborsUdpAck: '" << storeKeyText(key) << "' has no locks");
        neighborCountIgnored(p);
        return;
    }

    debugs(15, 3, "neighborsUdpAck: " << opcode_d << " for '" << storeKeyText(key) << "' from " << (p ? p->host : "source") << " ");

    if (p) {
        ntype = neighborType(p, mem->request);
    }

    if (ignoreMulticastReply(p, mem)) {
        neighborCountIgnored(p);
    } else if (opcode == ICP_MISS) {
        if (p == NULL) {
            neighborIgnoreNonPeer(from, opcode);
        } else {
            mem->ping_reply_callback(p, ntype, PROTO_ICP, header, mem->ircb_data);
        }
    } else if (opcode == ICP_HIT) {
        if (p == NULL) {
            neighborIgnoreNonPeer(from, opcode);
        } else {
            header->opcode = ICP_HIT;
            mem->ping_reply_callback(p, ntype, PROTO_ICP, header, mem->ircb_data);
        }
    } else if (opcode == ICP_DECHO) {
        if (p == NULL) {
            neighborIgnoreNonPeer(from, opcode);
        } else if (ntype == PEER_SIBLING) {
            debug_trap("neighborsUdpAck: Found non-ICP cache as SIBLING\n");
            debug_trap("neighborsUdpAck: non-ICP neighbors must be a PARENT\n");
        } else {
            mem->ping_reply_callback(p, ntype, PROTO_ICP, header, mem->ircb_data);
        }
    } else if (opcode == ICP_SECHO) {
        if (p) {
            debugs(15, 1, "Ignoring SECHO from neighbor " << p->host);
            neighborCountIgnored(p);
        } else {
            debugs(15, 1, "Unsolicited SECHO from " << from);
        }
    } else if (opcode == ICP_DENIED) {
        if (p == NULL) {
            neighborIgnoreNonPeer(from, opcode);
        } else if (p->stats.pings_acked > 100) {
            if (100 * p->icp.counts[ICP_DENIED] / p->stats.pings_acked > 95) {
                debugs(15, 0, "95%% of replies from '" << p->host << "' are UDP_DENIED");
                debugs(15, 0, "Disabling '" << p->host << "', please check your configuration.");
                neighborRemove(p);
                p = NULL;
            } else {
                neighborCountIgnored(p);
            }
        }
    } else if (opcode == ICP_MISS_NOFETCH) {
        mem->ping_reply_callback(p, ntype, PROTO_ICP, header, mem->ircb_data);
    } else {
        debugs(15, 0, "neighborsUdpAck: Unexpected ICP reply: " << opcode_d);
    }
}
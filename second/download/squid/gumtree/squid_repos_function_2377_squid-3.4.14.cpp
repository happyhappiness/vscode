static void
idnsGrokReply(const char *buf, size_t sz, int from_ns)
{
    int n;
    rfc1035_message *message = NULL;
    idns_query *q;

    n = rfc1035MessageUnpack(buf, sz, &message);

    if (message == NULL) {
        debugs(78, DBG_IMPORTANT, "idnsGrokReply: Malformed DNS response");
        return;
    }

    debugs(78, 3, "idnsGrokReply: QID 0x" << std::hex <<   message->id << ", " << std::dec << n << " answers");

    q = idnsFindQuery(message->id);

    if (q == NULL) {
        debugs(78, 3, "idnsGrokReply: Late response");
        rfc1035MessageDestroy(&message);
        return;
    }

    if (rfc1035QueryCompare(&q->query, message->query) != 0) {
        debugs(78, 3, "idnsGrokReply: Query mismatch (" << q->query.name << " != " << message->query->name << ")");
        rfc1035MessageDestroy(&message);
        return;
    }

#if WHEN_EDNS_RESPONSES_ARE_PARSED
// TODO: actually gr the message right here.
//	pull out the DNS meta data we need (A records, AAAA records and EDNS OPT) and store in q
//	this is overall better than force-feeding A response with AAAA an section later anyway.
//	AND allows us to merge AN+AR sections from both responses (one day)

    if (q->edns_seen >= 0) {
        if (max_shared_edns == nameservers[from_ns].last_seen_edns && max_shared_edns < q->edns_seen) {
            nameservers[from_ns].last_seen_edns = q->edns_seen;
            // the altered NS was limiting the whole group.
            max_shared_edns = q->edns_seen;
            // may be limited by one of the others still
            for (int i = 0; i < nns; ++i)
                max_shared_edns = min(max_shared_edns, nameservers[i].last_seen_edns);
        } else {
            nameservers[from_ns].last_seen_edns = q->edns_seen;
            // maybe reduce the global limit downwards to accomodate this NS
            max_shared_edns = min(max_shared_edns, q->edns_seen);
        }
        if (max_shared_edns < RFC1035_DEFAULT_PACKET_SZ)
            max_shared_edns = -1;
    }
#endif

    dlinkDelete(&q->lru, &lru_list);
    q->pending = 0;

    if (message->tc) {
        debugs(78, 3, HERE << "Resolver requested TC (" << q->query.name << ")");
        rfc1035MessageDestroy(&message);

        if (!q->need_vc) {
            q->need_vc = 1;
            -- q->nsends;
            idnsSendQuery(q);
        } else {
            // Strange: A TCP DNS response with the truncation bit (TC) set.
            // Return an error and cleanup; no point in trying TCP again.
            debugs(78, 3, HERE << "TCP DNS response");
            idnsCallback(q, "Truncated TCP DNS response");
        }

        return;
    }

    idnsRcodeCount(n, q->attempt);

    if (n < 0) {
        q->rcode = -n;
        debugs(78, 3, "idnsGrokReply: error " << rfc1035ErrorMessage(n) << " (" << q->rcode << ")");

        if (q->rcode == 2 && (++ q->attempt) < MAX_ATTEMPT) {
            /*
             * RCODE 2 is "Server failure - The name server was
             * unable to process this query due to a problem with
             * the name server."
             */
            debugs(78, 3, "idnsGrokReply: Query result: SERV_FAIL");
            rfc1035MessageDestroy(&message);
            idnsSendQuery(q);
            return;
        }

        // Do searchpath processing on the master A query only to keep
        // things simple. NXDOMAIN is authorative for the label, not
        // the record type.
        if (q->rcode == 3 && !q->master && q->do_searchpath && q->attempt < MAX_ATTEMPT) {
            assert(NULL == message->answer);
            strcpy(q->name, q->orig);

            debugs(78, 3, "idnsGrokReply: Query result: NXDOMAIN - " << q->name );

            if (q->domain < npc) {
                strcat(q->name, ".");
                strcat(q->name, searchpath[q->domain].domain);
                debugs(78, 3, "idnsGrokReply: searchpath used for " << q->name);
                ++ q->domain;
            } else {
                ++ q->attempt;
            }

            rfc1035MessageDestroy(&message);

            // cleanup slave AAAA query
            while (idns_query *slave = q->slave) {
                dlinkDelete(&slave->lru, &lru_list);
                q->slave = slave->slave;
                rfc1035MessageDestroy(&slave->message);
                cbdataFree(slave);
            }

            // Build new query
            q->query_id = idnsQueryID();
            debugs(78, 3, "idnsGrokReply: Trying A Query for " << q->name);
            // see EDNS notes at top of file why this sends 0
            q->sz = rfc3596BuildAQuery(q->name, q->buf, sizeof(q->buf), q->query_id, &q->query, 0);
            if (q->sz < 0) {
                /* problem with query data -- query not sent */
                idnsCallback(q, "Internal error");
                return;
            }

            q->nsends = 0;

            idnsCheckMDNS(q);
            idnsSendQuery(q);
            if (Ip::EnableIpv6)
                idnsSendSlaveAAAAQuery(q);
            return;
        }
    }

    q->message = message;
    q->ancount = n;

    if (n >= 0)
        idnsCallback(q, NULL);
    else
        idnsCallback(q, rfc1035ErrorMessage(q->rcode));

}
static void
idnsGrokReply(const char *buf, size_t sz)
{
    int n;
    rfc1035_message *message = NULL;
    idns_query *q;

    n = rfc1035MessageUnpack(buf, sz, &message);

    if (message == NULL) {
        debugs(78, 1, "idnsGrokReply: Malformed DNS response");
        return;
    }

    debugs(78, 3, "idnsGrokReply: ID 0x" << std::hex << message->id << ", " << std::dec << n << " answers");

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

    if (message->tc) {
        debugs(78, 3, HERE << "Resolver requested TC (" << q->query.name << ")");
        dlinkDelete(&q->lru, &lru_list);
        rfc1035MessageDestroy(&message);

        if (!q->need_vc) {
            q->need_vc = 1;
            q->nsends--;
            idnsSendQuery(q);
        }

        return;
    }

    dlinkDelete(&q->lru, &lru_list);
    idnsRcodeCount(n, q->attempt);
    q->error = NULL;

    if (n < 0) {
        debugs(78, 3, "idnsGrokReply: error " << rfc1035_error_message << " (" << rfc1035_errno << ")");

        q->error = rfc1035_error_message;
        q->rcode = -n;

        if (q->rcode == 2 && ++q->attempt < MAX_ATTEMPT) {
            /*
             * RCODE 2 is "Server failure - The name server was
             * unable to process this query due to a problem with
             * the name server."
             */
            debugs(78, 3, "idnsGrokReply: Query result: SERV_FAIL");
            rfc1035MessageDestroy(&message);
            q->start_t = current_time;
            q->id = idnsQueryID();
            rfc1035SetQueryID(q->buf, q->id);
            idnsSendQuery(q);
            return;
        }

        if (q->rcode == 3 && q->do_searchpath && q->attempt < MAX_ATTEMPT) {
            assert(NULL == message->answer);
            strcpy(q->name, q->orig);

            debugs(78, 3, "idnsGrokReply: Query result: NXDOMAIN - " << q->name );

            if (q->domain < npc) {
                strcat(q->name, ".");
                strcat(q->name, searchpath[q->domain].domain);
                debugs(78, 3, "idnsGrokReply: searchpath used for " << q->name);
                q->domain++;
            } else {
                q->attempt++;
            }

            idnsDropMessage(message, q);

            q->start_t = current_time;
            q->id = idnsQueryID();
            rfc1035SetQueryID(q->buf, q->id);
            if (Ip::EnableIpv6 && q->query.qtype == RFC1035_TYPE_AAAA) {
                debugs(78, 3, "idnsGrokReply: Trying AAAA Query for " << q->name);
                q->sz = rfc3596BuildAAAAQuery(q->name, q->buf, sizeof(q->buf), q->id, &q->query);
            } else {
                debugs(78, 3, "idnsGrokReply: Trying A Query for " << q->name);
                q->sz = rfc3596BuildAQuery(q->name, q->buf, sizeof(q->buf), q->id, &q->query);
            }

            if (q->sz < 0) {
                /* problem with query data -- query not sent */
                idnsCallback(static_cast<idns_query *>(q->callback_data), NULL, 0, "Internal error");
                cbdataFree(q);
                return;
            }

            idnsCacheQuery(q);
            idnsSendQuery(q);
            return;
        }
    }

    if (q->need_A && (Config.onoff.dns_require_A == 1 || n <= 0 ) ) {
        /* ERROR or NO AAAA exist. Failover to A records. */
        /*      Apparently its also a good idea to lookup and store the A records
         *      just in case the AAAA are not available when we need them.
         *      This could occur due to number of network failings beyond our control
         *      thus the || above allowing the user to request always both.
         */

        if (n == 0)
            debugs(78, 3, "idnsGrokReply: " << q->name << " has no AAAA records. Looking up A record instead.");
        else if (q->need_A && n <= 0)
            debugs(78, 3, "idnsGrokReply: " << q->name << " AAAA query failed. Trying A now instead.");
        else // admin requested this.
            debugs(78, 3, "idnsGrokReply: " << q->name << " AAAA query done. Configured to retrieve A now also.");

        // move the initial message results into the failover query for merging later.
        if (n > 0) {
            q->initial_AAAA.count = message->ancount;
            q->initial_AAAA.answers = message->answer;
            message->answer = NULL;
        }

        // remove the hashed query info
        idnsDropMessage(message, q);

        // reset the query as an A query
        q->nsends = 0;
        q->start_t = current_time;
        q->id = idnsQueryID();
        rfc1035SetQueryID(q->buf, q->id);
        q->sz = rfc3596BuildAQuery(q->name, q->buf, sizeof(q->buf), q->id, &q->query);
        q->need_A = false;

        if (q->sz < 0) {
            /* problem with query data -- query not sent */
            idnsCallback(static_cast<idns_query *>(q->callback_data), NULL, 0, "Internal error");
            cbdataFree(q);
            return;
        }

        idnsCacheQuery(q);
        idnsSendQuery(q);
        return;
    }

    /** If there are two result sets from preceeding AAAA and A lookups merge them with a preference for AAAA */
    if (q->initial_AAAA.count > 0 && n > 0) {
        /* two sets of RR need merging */
        rfc1035_rr *result = (rfc1035_rr*) xmalloc( sizeof(rfc1035_rr)*(n + q->initial_AAAA.count) );
        rfc1035_rr *tmp = result;

        debugs(78, 6, HERE << "Merging DNS results " << q->name << " AAAA has " << q->initial_AAAA.count << " RR, A has " << n << " RR");

        if (Config.dns.v4_first) {
            memcpy( tmp, message->answer, (sizeof(rfc1035_rr)*n) );
            tmp += n;
            /* free the RR object without freeing its child strings (they are now taken by the copy above) */
            safe_free(message->answer);
        }

        memcpy(tmp, q->initial_AAAA.answers, (sizeof(rfc1035_rr)*(q->initial_AAAA.count)) );
        tmp += q->initial_AAAA.count;
        /* free the RR object without freeing its child strings (they are now taken by the copy above) */
        safe_free(q->initial_AAAA.answers);

        if (!Config.dns.v4_first) {
            memcpy( tmp, message->answer, (sizeof(rfc1035_rr)*n) );
            /* free the RR object without freeing its child strings (they are now taken by the copy above) */
            safe_free(message->answer);
        }

        n += q->initial_AAAA.count;
        q->initial_AAAA.count = 0;
        message->answer = result;
        message->ancount = n;
    } else if (q->initial_AAAA.count > 0 && n <= 0) {
        /* initial of dual queries was the only result set. */
        debugs(78, 6, HERE << "Merging DNS results " << q->name << " AAAA has " << q->initial_AAAA.count << " RR, A has " << n << " RR");
        rfc1035RRDestroy(&(message->answer), n);
        message->answer = q->initial_AAAA.answers;
        n = q->initial_AAAA.count;
        message->ancount = n;
    }
    /* else initial results were empty. just use the final set as authoritative */

    debugs(78, 6, HERE << "Sending " << n << " DNS results to caller.");
    idnsCallback(q, message->answer, n, q->error);
    rfc1035MessageDestroy(&message);
    cbdataFree(q);
}
static void
idnsCheckQueue(void *)
{
    dlink_node *n;
    dlink_node *p = NULL;
    idns_query *q;
    event_queued = 0;

    if (0 == nns)
        /* name servers went away; reconfiguring or shutting down */
        return;

    for (n = lru_list.tail; n; n = p) {

        p = n->prev;
        q = static_cast<idns_query*>(n->data);

        /* Anything to process in the queue? */
        if ((time_msec_t)tvSubMsec(q->queue_t, current_time) < Config.Timeout.idns_retransmit )
            break;

        /* Query timer still running? */
        if ((time_msec_t)tvSubMsec(q->sent_t, current_time) < (Config.Timeout.idns_retransmit * 1 << ((q->nsends - 1) / nns))) {
            dlinkDelete(&q->lru, &lru_list);
            q->queue_t = current_time;
            dlinkAdd(q, &q->lru, &lru_list);
            continue;
        }

        debugs(78, 3, "idnsCheckQueue: ID " << q->xact_id <<
               " QID 0x"  << std::hex << std::setfill('0')  <<
               std::setw(4) << q->query_id << ": timeout" );

        dlinkDelete(&q->lru, &lru_list);
        q->pending = 0;

        if ((time_msec_t)tvSubMsec(q->start_t, current_time) < Config.Timeout.idns_query) {
            idnsSendQuery(q);
        } else {
            debugs(78, 2, "idnsCheckQueue: ID " << q->xact_id <<
                   " QID 0x" << std::hex << q->query_id <<
                   " : giving up after " << std::dec << q->nsends << " tries and " <<
                   std::setw(5)<< std::setprecision(2) << tvSubDsec(q->start_t, current_time) << " seconds");

            if (q->rcode != 0)
                idnsCallback(q, rfc1035ErrorMessage(q->rcode));
            else
                idnsCallback(q, "Timeout");
        }
    }

    idnsTickleQueue();
}
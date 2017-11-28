static void
idnsCheckQueue(void *unused)
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
        if (tvSubDsec(q->queue_t, current_time) < Config.Timeout.idns_retransmit )
            break;

        /* Query timer expired? */
        if (tvSubDsec(q->sent_t, current_time) < Config.Timeout.idns_retransmit * 1 << ((q->nsends - 1) / nns)) {
            dlinkDelete(&q->lru, &lru_list);
            q->queue_t = current_time;
            dlinkAdd(q, &q->lru, &lru_list);
            continue;
        }

        debugs(78, 3, "idnsCheckQueue: ID 0x" << std::hex << std::setfill('0') << std::setw(4) << q->id << "timeout" );

        dlinkDelete(&q->lru, &lru_list);

        if (tvSubDsec(q->start_t, current_time) < Config.Timeout.idns_query) {
            idnsSendQuery(q);
        } else {
            debugs(78, 2, "idnsCheckQueue: ID " << std::hex << q->id <<
                   ": giving up after " << std::dec << q->nsends << " tries and " <<
                   std::setw(5)<< std::setprecision(2) << tvSubDsec(q->start_t, current_time) << " seconds");

            if (q->rcode != 0)
                idnsCallback(q, NULL, -q->rcode, q->error);
            else
                idnsCallback(q, NULL, -16, "Timeout");

            cbdataFree(q);
        }
    }

    idnsTickleQueue();
}
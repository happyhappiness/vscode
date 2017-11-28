static void
idnsCallback(idns_query *q, const char *error)
{
    IDNSCB *callback;
    void *cbdata;

    if (error)
        q->error = error;

    if (q->master)
        q = q->master;

    // If any of our subqueries are still pending then wait for them to complete before continuing
    for (idns_query *q2 = q; q2; q2 = q2->slave) {
        if (q2->pending) {
            return;
        }
    }

    /* Merge results */
    rfc1035_message *message = q->message;
    q->message = NULL;
    int n = q->ancount;
    error = q->error;

    while ( idns_query *q2 = q->slave ) {
        debugs(78, 6, HERE << "Merging DNS results " << q->name << " A has " << n << " RR, AAAA has " << q2->ancount << " RR");
        q->slave = q2->slave;
        if ( !q2->error ) {
            if (n > 0) {
                // two sets of RR need merging
                rfc1035_rr *result = (rfc1035_rr*) xmalloc( sizeof(rfc1035_rr)*(n + q2->ancount) );
                if (Config.dns.v4_first) {
                    memcpy(result, message->answer, (sizeof(rfc1035_rr)*n) );
                    memcpy(result+n, q2->message->answer, (sizeof(rfc1035_rr)*q2->ancount) );
                } else {
                    memcpy(result, q2->message->answer, (sizeof(rfc1035_rr)*q2->ancount) );
                    memcpy(result+q2->ancount, message->answer, (sizeof(rfc1035_rr)*n) );
                }
                n += q2->ancount;
                // HACK WARNING, the answer rr:s have been copied in-place to
                // result, do not free them here
                safe_free(message->answer);
                safe_free(q2->message->answer);
                message->answer = result;
                message->ancount += q2->message->ancount;
            } else {
                // first response empty or failed, just use the second
                rfc1035MessageDestroy(&message);
                message = q2->message;
                q2->message = NULL;
                n = q2->ancount;
                error = NULL;
            }
        }
        rfc1035MessageDestroy(&q2->message);
        cbdataFree(q2);
    }

    debugs(78, 6, HERE << "Sending " << n << " (" << (error ? error : "OK") << ") DNS results to caller.");

    callback = q->callback;
    q->callback = NULL;
    const rfc1035_rr *answers = message ? message->answer : NULL;

    if (cbdataReferenceValidDone(q->callback_data, &cbdata))
        callback(cbdata, answers, n, error);

    while (q->queue) {
        idns_query *q2 = q->queue;
        q->queue = q2->queue;
        callback = q2->callback;
        q2->callback = NULL;

        if (cbdataReferenceValidDone(q2->callback_data, &cbdata))
            callback(cbdata, answers, n, error);

        cbdataFree(q2);
    }

    if (q->hash.key) {
        hash_remove_link(idns_lookup_hash, &q->hash);
        q->hash.key = NULL;
    }

    rfc1035MessageDestroy(&message);
    cbdataFree(q);
}
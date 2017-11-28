static void
idnsCallback(idns_query *q, rfc1035_rr *answers, int n, const char *error)
{
    IDNSCB *callback;
    void *cbdata;

    callback = q->callback;
    q->callback = NULL;

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
}
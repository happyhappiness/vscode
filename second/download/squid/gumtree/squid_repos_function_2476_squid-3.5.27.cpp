static int
idnsCachedLookup(const char *key, IDNSCB * callback, void *data)
{
    idns_query *q;

    idns_query *old = (idns_query *) hash_lookup(idns_lookup_hash, key);

    if (!old)
        return 0;

    q = cbdataAlloc(idns_query);
    // idns_query is POD so no constructors are called after allocation
    q->xact_id.change();
    // no query_id on this instance.

    q->callback = callback;

    q->callback_data = cbdataReference(data);

    q->queue = old->queue;

    old->queue = q;

    return 1;
}
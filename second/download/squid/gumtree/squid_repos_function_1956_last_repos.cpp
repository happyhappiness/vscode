static int
idnsCachedLookup(const char *key, IDNSCB * callback, void *data)
{
    idns_query *old = (idns_query *) hash_lookup(idns_lookup_hash, key);

    if (!old)
        return 0;

    idns_query *q = new idns_query;
    // no query_id on this instance.

    q->callback = callback;
    q->callback_data = cbdataReference(data);

    q->queue = old->queue;
    old->queue = q;

    return 1;
}
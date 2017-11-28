static void
idnsStartQuery(idns_query *q, IDNSCB * callback, void *data)
{
    q->start_t = current_time;
    q->callback = callback;
    q->callback_data = cbdataReference(data);

    q->hash.key = q->orig;
    hash_join(idns_lookup_hash, &q->hash);

    idnsSendQuery(q);
}
void
idnsDropMessage(rfc1035_message *message, idns_query *q)
{
    rfc1035MessageDestroy(&message);
    if (q->hash.key) {
        hash_remove_link(idns_lookup_hash, &q->hash);
        q->hash.key = NULL;
    }
}
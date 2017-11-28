static void
idnsCacheQuery(idns_query *q)
{
    q->hash.key = q->query.name;
    hash_join(idns_lookup_hash, &q->hash);
}
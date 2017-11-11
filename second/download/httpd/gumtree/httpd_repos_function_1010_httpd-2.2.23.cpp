void cache_free(cache_cache_t *c)
{
    cache_pq_free(c->pq);
    cache_hash_free(c->ht);
    free(c);
}
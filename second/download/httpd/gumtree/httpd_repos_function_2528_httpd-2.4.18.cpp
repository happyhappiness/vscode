h2_stream_set *h2_stream_set_create(apr_pool_t *pool, int max)
{
    h2_stream_set *sp = apr_pcalloc(pool, sizeof(h2_stream_set));
    sp->hash = apr_hash_make_custom(pool, stream_hash);

    return sp;
}
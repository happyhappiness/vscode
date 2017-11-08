h2_stream_set *h2_stream_set_create(apr_pool_t *pool)
{
    h2_stream_set *sp = apr_pcalloc(pool, sizeof(h2_stream_set));
    if (sp) {
        sp->list = apr_array_make(pool, 100, sizeof(h2_stream*));
        if (!sp->list) {
            return NULL;
        }
    }
    return sp;
}
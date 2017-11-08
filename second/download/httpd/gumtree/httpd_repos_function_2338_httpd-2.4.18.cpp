h2_io_set *h2_io_set_create(apr_pool_t *pool)
{
    h2_io_set *sp = apr_pcalloc(pool, sizeof(h2_io_set));
    if (sp) {
        sp->list = apr_array_make(pool, 100, sizeof(h2_io*));
        if (!sp->list) {
            return NULL;
        }
    }
    return sp;
}
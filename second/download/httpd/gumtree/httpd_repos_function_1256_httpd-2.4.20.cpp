static int cache_header_cmp(apr_pool_t *pool, apr_table_t *left,
        apr_table_t *right, const char *key)
{
    const char *h1, *h2;

    if ((h1 = cache_table_getm(pool, left, key))
            && (h2 = cache_table_getm(pool, right, key)) && (strcmp(h1, h2))) {
        return 1;
    }
    return 0;
}
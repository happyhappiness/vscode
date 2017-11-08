static const char *cache_header_cmp(apr_pool_t *pool, apr_table_t *left,
        apr_table_t *right, const char *key)
{
    const char *h1, *h2;

    if ((h1 = cache_table_getm(pool, left, key))
            && (h2 = cache_table_getm(pool, right, key)) && (strcmp(h1, h2))) {
        return apr_pstrcat(pool, "contradiction: 304 Not Modified, but ", key,
                " modified", NULL);
    }
    return NULL;
}
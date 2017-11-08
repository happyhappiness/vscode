static bndm_t *bndm_compile(apr_pool_t *pool, const char *n, apr_size_t nl)
{
    unsigned int x;
    const char *ne = n + nl;
    bndm_t *t = apr_palloc(pool, sizeof(*t));

    memset(t->T, 0, sizeof(unsigned int) * 256);
    t->pattern_len = nl;

    for (x = 1; n < ne; x <<= 1) {
        t->T[(unsigned char) *n++] |= x;
    }

    t->x = x - 1;

    return t;
}
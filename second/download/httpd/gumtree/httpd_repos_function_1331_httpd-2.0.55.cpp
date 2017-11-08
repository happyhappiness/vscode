static void bndm_compile(bndm_t *t, const char *n, apr_size_t nl)
{
    unsigned int x;
    const char *ne = n + nl;

    memset(t->T, 0, sizeof(unsigned int) * 256);
    
    for (x = 1; n < ne; x <<= 1)
        t->T[(unsigned char) *n++] |= x;

    t->x = x - 1;
}
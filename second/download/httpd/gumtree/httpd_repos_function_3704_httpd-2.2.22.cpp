static void apr_random_bytes(apr_random_t *g,unsigned char *random,
                             apr_size_t bytes)
{
    apr_size_t n;

    for (n = 0; n < bytes; ) {
        apr_size_t l;

        if (g->random_bytes == 0) {
            apr_random_block(g,g->randomness);
            g->random_bytes = B_size(g);
        }
        l = min(bytes-n,g->random_bytes);
        memcpy(&random[n],g->randomness+B_size(g)-g->random_bytes,l);
        g->random_bytes-=l;
        n+=l;
    }
}
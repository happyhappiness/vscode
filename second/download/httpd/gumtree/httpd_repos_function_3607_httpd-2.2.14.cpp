static void rekey(apr_random_t *g)
{
    unsigned int n;
    unsigned char *H = H_current(g);

    hash_init(g->key_hash);
    hash_add(g->key_hash,H,H_size(g));
    for (n = 0 ; n < g->npools && (n == 0 || g->generation&(1 << (n-1)))
            ; ++n) {
        hash_add(g->key_hash,g->pools[n].pool,g->pools[n].bytes);
        g->pools[n].bytes = 0;
    }
    hash_finish(g->key_hash,H+B_size(g));

    ++g->generation;
    if (!g->insecure_started && g->generation > g->g_for_insecure) {
        g->insecure_started = 1;
        if (!g->secure_started) {
            memcpy(g->H_waiting,g->H,H_size(g));
            g->secure_base = g->generation;
        }
    }

    if (!g->secure_started && g->generation > g->secure_base+g->g_for_secure) {
        g->secure_started = 1;
        memcpy(g->H,g->H_waiting,H_size(g));
    }
}
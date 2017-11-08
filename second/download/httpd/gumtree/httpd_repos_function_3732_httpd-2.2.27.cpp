static void apr_random_block(apr_random_t *g,unsigned char *random)
{
    /* FIXME: in principle, these are different hashes */
    hash(g->prng_hash,g->H,g->H,H_size(g));
    hash(g->prng_hash,random,g->H,B_size(g));
}
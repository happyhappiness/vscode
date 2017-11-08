static void mix_pid(apr_random_t *g,unsigned char *H,pid_t pid)
{
    hash_init(g->key_hash);
    hash_add(g->key_hash,H,H_size(g));
    hash_add(g->key_hash,&pid,sizeof pid);
    hash_finish(g->key_hash,H);
}
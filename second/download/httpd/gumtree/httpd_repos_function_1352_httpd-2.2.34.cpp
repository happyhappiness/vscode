static void *create_cgid_dirconf(apr_pool_t *p, char *dummy)
{
    cgid_dirconf *c = (cgid_dirconf *) apr_pcalloc(p, sizeof(cgid_dirconf));
    return c;
}
static void *create_cgid_config(apr_pool_t *p, server_rec *s)
{
    cgid_server_conf *c =
    (cgid_server_conf *) apr_pcalloc(p, sizeof(cgid_server_conf));

    c->logname = NULL;
    c->logbytes = DEFAULT_LOGBYTES;
    c->bufbytes = DEFAULT_BUFBYTES;
    return c;
}
static void *create_deflate_server_config(apr_pool_t *p, server_rec *s)
{
    deflate_filter_config *c = apr_pcalloc(p, sizeof *c);

    c->memlevel   = DEFAULT_MEMLEVEL;
    c->windowSize = DEFAULT_WINDOWSIZE;
    c->bufferSize = DEFAULT_BUFFERSIZE;
    c->compressionlevel = DEFAULT_COMPRESSION;

    return c;
}
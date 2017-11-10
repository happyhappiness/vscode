static void *create_bucketeer_server_config(apr_pool_t *p, server_rec *s)
{
    bucketeer_filter_config_t *c = apr_pcalloc(p, sizeof *c);

    c->bucketdelimiter = 0x02; /* ^B */
    c->passdelimiter = 0x10;   /* ^P */
    c->flushdelimiter = 0x06;  /* ^F */

    return c;
}
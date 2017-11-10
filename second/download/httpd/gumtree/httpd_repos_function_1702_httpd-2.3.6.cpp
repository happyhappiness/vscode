static void *create_config(apr_pool_t *p, server_rec *s)
{
    connect_conf *c = apr_pcalloc(p, sizeof(connect_conf));
    c->allowed_connect_ports = apr_array_make(p, 10, sizeof(port_range));
    return c;
}
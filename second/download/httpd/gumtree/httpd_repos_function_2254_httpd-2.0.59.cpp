static void *perchild_create_config(apr_pool_t *p, server_rec *s)
{
    perchild_server_conf *c = (perchild_server_conf *)
                                  apr_pcalloc(p, sizeof(perchild_server_conf));

    c->input = -1;
    c->output = -1;
    return c;
}
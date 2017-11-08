static void *server_create(apr_pool_t *p, server_rec *s)
{
    express_server_conf *a;

    a = (express_server_conf *)apr_pcalloc(p, sizeof(express_server_conf));

    a->dbmfile = NULL;
    a->dbmtype = "default";
    a->enabled = 0;

    return (void *)a;
}
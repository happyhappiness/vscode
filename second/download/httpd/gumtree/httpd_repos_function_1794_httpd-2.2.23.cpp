static void *nwssl_config_server_create(apr_pool_t *p, server_rec *s)
{
    NWSSLSrvConfigRec *new = apr_palloc(p, sizeof(NWSSLSrvConfigRec));
    new->sltable = apr_table_make(p, 5);
    new->slutable = apr_table_make(p, 5);
    return new;
}
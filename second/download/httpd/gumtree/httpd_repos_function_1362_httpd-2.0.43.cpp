static int isSecure (const request_rec *r)
{
    NWSSLSrvConfigRec *sc = get_nwssl_cfg(r->server);
    const char *s_secure = NULL;
    char port[8];
    int ret = 0;

    itoa(((r->connection)->local_addr)->port, port, 10);
    s_secure = apr_table_get(sc->sltable, port);    
    if (s_secure)
        ret = 1;

    return ret;
}
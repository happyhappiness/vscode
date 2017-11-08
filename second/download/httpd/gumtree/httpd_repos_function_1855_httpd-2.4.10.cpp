static void *create_echo_server_config(apr_pool_t *p, server_rec *s)
{
    EchoConfig *pConfig = apr_pcalloc(p, sizeof *pConfig);

    pConfig->bEnabled = 0;

    return pConfig;
}
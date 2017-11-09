static int ef_init(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *main_s)
{
    main_server = main_s;
    return OK;
}
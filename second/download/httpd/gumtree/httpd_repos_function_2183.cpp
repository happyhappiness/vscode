static int pre_config(apr_pool_t *p, apr_pool_t *plog,
                      apr_pool_t *ptemp)
{
    gpool = p;
    return OK;
}
static int authz_core_pre_config(apr_pool_t *p, apr_pool_t *plog,
                                 apr_pool_t *ptemp)
{
    authz_core_first_dir_conf = NULL;

    return OK;
}
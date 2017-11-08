static int dbd_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                          apr_pool_t *ptemp)
{
   config_pool = pconf;
   group_list = NULL;
   return OK;
}
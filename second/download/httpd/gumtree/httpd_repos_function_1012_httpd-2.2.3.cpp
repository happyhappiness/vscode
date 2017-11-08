static int dbd_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
   dbd_prepared_defns = apr_hash_make(ptemp);
   return OK;
}
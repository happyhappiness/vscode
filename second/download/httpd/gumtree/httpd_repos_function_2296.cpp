static int 
netware_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                 apr_pool_t *ptemp)
{
    ap_sys_privileges_handlers(1);
    return OK;
}
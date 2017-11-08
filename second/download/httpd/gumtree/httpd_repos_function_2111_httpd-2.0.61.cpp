static void beos_hooks(apr_pool_t *p)
{
    one_process = 0;
    
    ap_hook_pre_config(beos_pre_config, NULL, NULL, APR_HOOK_REALLY_FIRST); 
}
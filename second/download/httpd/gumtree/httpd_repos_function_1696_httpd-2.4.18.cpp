static void macro_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(macro_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
}
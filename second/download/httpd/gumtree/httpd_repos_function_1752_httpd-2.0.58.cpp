static void register_hooks(apr_pool_t *p)
{
    ap_hook_access_checker(check_dir_access,NULL,NULL,APR_HOOK_MIDDLE);
}
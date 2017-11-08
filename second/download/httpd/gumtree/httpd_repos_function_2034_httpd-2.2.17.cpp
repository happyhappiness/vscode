static void register_hooks(apr_pool_t *p)
{
    /* This can be access checker since we don't require r->user to be set. */
    ap_hook_access_checker(check_dir_access,NULL,NULL,APR_HOOK_MIDDLE);
}
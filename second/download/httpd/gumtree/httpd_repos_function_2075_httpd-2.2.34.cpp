static void register_hooks(apr_pool_t *p)
{
    ap_hook_auth_checker(check_user_access, NULL, NULL, APR_HOOK_MIDDLE);
}
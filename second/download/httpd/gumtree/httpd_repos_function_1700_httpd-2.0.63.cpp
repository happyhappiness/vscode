static void register_hooks(apr_pool_t *p)
{
    ap_hook_check_user_id(anon_authenticate_basic_user,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_auth_checker(check_anon_access,NULL,NULL,APR_HOOK_MIDDLE);
}
static void register_hooks(apr_pool_t *p)
{
    ap_hook_check_user_id(authenticate_no_user,NULL,NULL,APR_HOOK_LAST);
}
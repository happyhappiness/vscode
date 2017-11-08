static void unixd_hooks(apr_pool_t *pool)
{
    ap_hook_pre_config(unixd_pre_config,
                       NULL, NULL, APR_HOOK_FIRST);

    ap_hook_drop_privileges(unixd_drop_privileges,
                            NULL, NULL, APR_HOOK_MIDDLE);
}
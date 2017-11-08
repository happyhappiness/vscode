static void register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(access_compat_ap_satisfies);

    /* This can be access checker since we don't require r->user to be set. */
    ap_hook_check_access(check_dir_access, NULL, NULL, APR_HOOK_MIDDLE,
                         AP_AUTH_INTERNAL_PER_CONF);
}
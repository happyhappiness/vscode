static void register_hooks(apr_pool_t *p)
{
    ap_hook_check_authn(authenticate_basic_user, NULL, NULL, APR_HOOK_MIDDLE,
                        AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_fixups(authenticate_basic_fake, NULL, NULL, APR_HOOK_LAST);
    ap_hook_note_auth_failure(hook_note_basic_auth_failure, NULL, NULL,
                              APR_HOOK_MIDDLE);
}
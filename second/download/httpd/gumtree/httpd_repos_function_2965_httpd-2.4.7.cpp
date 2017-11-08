static void register_hooks(apr_pool_t * p)
{
#if AP_MODULE_MAGIC_AT_LEAST(20080403,1)
    ap_hook_check_authn(authenticate_form_authn, NULL, NULL, APR_HOOK_MIDDLE,
                        AP_AUTH_INTERNAL_PER_CONF);
#else
    ap_hook_check_user_id(authenticate_form_authn, NULL, NULL, APR_HOOK_MIDDLE);
#endif
    ap_hook_handler(authenticate_form_login_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(authenticate_form_logout_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(authenticate_form_redirect_handler, NULL, NULL, APR_HOOK_MIDDLE);

    ap_hook_note_auth_failure(hook_note_cookie_auth_failure, NULL, NULL,
                              APR_HOOK_MIDDLE);
}
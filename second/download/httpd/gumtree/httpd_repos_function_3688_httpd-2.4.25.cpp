static void fcgi_register_hooks(apr_pool_t *p)
{
    static const char * const auth_basic_runs_after_me[] = 
        {"mod_auth_basic.c", NULL}; /* to allow for custom response */

    ap_hook_pre_config(fcgi_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_check_authn(fcgi_check_authn, NULL, auth_basic_runs_after_me,
                        APR_HOOK_MIDDLE, AP_AUTH_INTERNAL_PER_CONF);
}
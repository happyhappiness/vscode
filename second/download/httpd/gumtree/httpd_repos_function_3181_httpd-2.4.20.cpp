static void register_hooks(apr_pool_t * p)
{
    ap_hook_session_load(session_cookie_load, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_session_save(session_cookie_save, NULL, NULL, APR_HOOK_MIDDLE);
}
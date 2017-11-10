static void register_hooks(apr_pool_t * p)
{
    ap_hook_session_load(session_dbd_load, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_session_save(session_dbd_save, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_monitor(session_dbd_monitor, NULL, NULL, APR_HOOK_MIDDLE);
}
static void noloris_hooks(apr_pool_t *p)
{
    ap_hook_process_connection(noloris_conn, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_pre_config(noloris_pre, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(noloris_post, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_monitor(noloris_monitor, NULL, NULL, APR_HOOK_MIDDLE);
}
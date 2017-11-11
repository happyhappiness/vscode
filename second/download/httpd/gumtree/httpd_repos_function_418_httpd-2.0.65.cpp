static void register_hooks(apr_pool_t *p)
{
    static const char * const pre[] = { "mod_unique_id.c", NULL };

    ap_hook_open_logs(log_init,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_post_read_request(log_before,pre,NULL,APR_HOOK_REALLY_FIRST);
    ap_hook_log_transaction(log_after,NULL,NULL,APR_HOOK_REALLY_LAST);
}
static void winnt_hooks(apr_pool_t *p)
{
    /* The prefork open_logs phase must run before the core's, or stderr
     * will be redirected to a file, and the messages won't print to the
     * console.
     */
    static const char *const aszSucc[] = {"core.c", NULL};

    ap_hook_pre_config(winnt_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(winnt_post_config, NULL, NULL, 0);
    ap_hook_child_init(winnt_child_init, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_open_logs(winnt_open_logs, NULL, aszSucc, APR_HOOK_MIDDLE);
}
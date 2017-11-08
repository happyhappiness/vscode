static void worker_hooks(apr_pool_t *p)
{
    /* The worker open_logs phase must run before the core's, or stderr
     * will be redirected to a file, and the messages won't print to the
     * console.
     */
    static const char *const aszSucc[] = {"core.c", NULL};
    one_process = 0;

    ap_hook_open_logs(worker_open_logs, NULL, aszSucc, APR_HOOK_MIDDLE);
    ap_hook_pre_config(worker_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
}
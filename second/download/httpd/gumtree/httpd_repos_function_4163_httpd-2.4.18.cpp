static void worker_hooks(apr_pool_t *p)
{
    /* Our open_logs hook function must run before the core's, or stderr
     * will be redirected to a file, and the messages won't print to the
     * console.
     */
    static const char *const aszSucc[] = {"core.c", NULL};
    one_process = 0;

    ap_hook_open_logs(worker_open_logs, NULL, aszSucc, APR_HOOK_REALLY_FIRST);
    /* we need to set the MPM state before other pre-config hooks use MPM query
     * to retrieve it, so register as REALLY_FIRST
     */
    ap_hook_pre_config(worker_pre_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
    ap_hook_check_config(worker_check_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_mpm(worker_run, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_mpm_query(worker_query, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_mpm_get_name(worker_get_name, NULL, NULL, APR_HOOK_MIDDLE);
}
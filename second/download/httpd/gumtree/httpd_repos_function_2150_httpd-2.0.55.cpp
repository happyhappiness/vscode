static void prefork_hooks(apr_pool_t *p)
{
    /* The prefork open_logs phase must run before the core's, or stderr
     * will be redirected to a file, and the messages won't print to the
     * console.
     */
    static const char *const aszSucc[] = {"core.c", NULL};

#ifdef AUX3
    (void) set42sig();
#endif

    ap_hook_open_logs(prefork_open_logs, NULL, aszSucc, APR_HOOK_MIDDLE);
    /* we need to set the MPM state before other pre-config hooks use MPM query
     * to retrieve it, so register as REALLY_FIRST
     */
    ap_hook_pre_config(prefork_pre_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
}
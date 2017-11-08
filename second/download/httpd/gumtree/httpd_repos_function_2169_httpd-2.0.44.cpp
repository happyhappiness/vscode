static void perchild_hooks(apr_pool_t *p)
{
    /* The perchild open_logs phase must run before the core's, or stderr
     * will be redirected to a file, and the messages won't print to the
     * console.
     */
    static const char *const aszSucc[] = {"core.c", NULL};
    one_process = 0;

    ap_hook_open_logs(perchild_open_logs, NULL, aszSucc, APR_HOOK_MIDDLE);
    ap_hook_pre_config(perchild_pre_config, NULL, NULL, APR_HOOK_MIDDLE); 
    ap_hook_post_config(perchild_post_config, NULL, NULL, APR_HOOK_MIDDLE); 

    /* Both of these must be run absolutely first.  If this request isn't for 
     * this server then we need to forward it to the proper child.  No sense
     * tying up this server running more post_read request hooks if it is
     * just going to be forwarded along.  The process_connection hook allows
     * perchild to receive the passed request correctly, by automatically
     * filling in the core_input_filter's ctx pointer.
     */
    ap_hook_post_read_request(perchild_post_read, NULL, NULL,
                              APR_HOOK_REALLY_FIRST);
    ap_hook_process_connection(perchild_process_connection, NULL, NULL, 
                               APR_HOOK_REALLY_FIRST);
}
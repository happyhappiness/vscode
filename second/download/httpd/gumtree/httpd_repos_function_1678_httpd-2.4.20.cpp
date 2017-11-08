static void wd_register_hooks(apr_pool_t *p)
{

    /* Only the mpm_winnt has child init hook handler.
     * Make sure that we are called after the mpm child init handler
     * initializes.
     */
    static const char *const after_mpm[]      = { "mpm_winnt.c", NULL};

    /* Pre config handling
     */
    ap_hook_pre_config(wd_pre_config_hook,
                       NULL,
                       NULL,
                       APR_HOOK_FIRST);

    /* Post config handling
     */
    ap_hook_post_config(wd_post_config_hook,
                        NULL,
                        NULL,
                        APR_HOOK_LAST);

    /* Child init hook
     */
    ap_hook_child_init(wd_child_init_hook,
                       after_mpm,
                       NULL,
                       APR_HOOK_MIDDLE);

    APR_REGISTER_OPTIONAL_FN(ap_watchdog_get_instance);
    APR_REGISTER_OPTIONAL_FN(ap_watchdog_register_callback);
    APR_REGISTER_OPTIONAL_FN(ap_watchdog_set_callback_interval);
}
static void hb_register_hooks(apr_pool_t *p)
{
    ap_hook_watchdog_need(hb_watchdog_need, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_watchdog_init(hb_watchdog_init, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_watchdog_step(hb_watchdog_step, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_watchdog_exit(hb_watchdog_exit, NULL, NULL, APR_HOOK_MIDDLE);
}
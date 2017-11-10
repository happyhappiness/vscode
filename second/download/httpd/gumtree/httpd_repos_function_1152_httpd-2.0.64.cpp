static void register_hooks(apr_pool_t *p)
{
    ap_hook_handler(status_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(status_init, NULL, NULL, APR_HOOK_MIDDLE);
#ifdef HAVE_TIMES
    ap_hook_child_init(status_child_init, NULL, NULL, APR_HOOK_MIDDLE);
#endif
}
static void register_hooks(apr_pool_t * p)
{
    ap_hook_handler(display_info, NULL, NULL, APR_HOOK_MIDDLE);
}
static void reflector_hooks(apr_pool_t * p)
{
    ap_hook_handler(reflector_handler, NULL, NULL, APR_HOOK_MIDDLE);
}
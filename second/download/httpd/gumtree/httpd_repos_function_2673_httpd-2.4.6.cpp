static void isapi_hooks(apr_pool_t *cont)
{
    ap_hook_pre_config(isapi_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(isapi_handler, NULL, NULL, APR_HOOK_MIDDLE);
}
static void register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(ap_cgi_build_command);
    ap_hook_pre_config(win32_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
}
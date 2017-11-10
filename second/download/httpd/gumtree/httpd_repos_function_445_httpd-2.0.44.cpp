static void register_hooks(apr_pool_t *p)
{
    ap_hook_fixups(fixup_env_module, NULL, NULL, APR_HOOK_MIDDLE);
}
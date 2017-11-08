static void register_hooks(apr_pool_t *p)
{
    ap_hook_fixups(fixup_dir,NULL,NULL,APR_HOOK_LAST);
}
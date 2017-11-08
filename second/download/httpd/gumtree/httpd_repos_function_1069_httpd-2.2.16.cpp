static void register_hooks(apr_pool_t *p)
{
    /* the order of these is of no consequence */
    ap_hook_fixups(fixup_dir,NULL,NULL,APR_HOOK_LAST);
    ap_hook_fixups(fixup_dflt,NULL,NULL,APR_HOOK_LAST);
}
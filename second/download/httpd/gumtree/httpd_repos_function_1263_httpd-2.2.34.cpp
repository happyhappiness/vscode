static void register_hooks(apr_pool_t *p)
{
    ap_hook_fixups(fix_encoding,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_type_checker(handle_multi,NULL,NULL,APR_HOOK_FIRST);
    ap_hook_handler(handle_map_file,NULL,NULL,APR_HOOK_MIDDLE);
}
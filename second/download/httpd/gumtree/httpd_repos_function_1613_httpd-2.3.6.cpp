static void register_hooks(apr_pool_t *p)
{
    ap_hook_post_config(mime_post_config,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_type_checker(find_ct,NULL,NULL,APR_HOOK_MIDDLE);
    /*
     * this hook seems redundant ... is there any reason a type checker isn't
     * allowed to do this already?  I'd think that fixups in general would be
     * the last opportunity to get the filters right.
     * ap_hook_insert_filter(mime_insert_filters,NULL,NULL,APR_HOOK_MIDDLE);
     */
}
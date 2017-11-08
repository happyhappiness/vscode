static void register_hooks(apr_pool_t *p)
{
    ap_hook_handler(dav_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(dav_init_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_fixups(dav_fixups, NULL, NULL, APR_HOOK_MIDDLE);

    dav_hook_find_liveprop(dav_core_find_liveprop, NULL, NULL, APR_HOOK_LAST);
    dav_hook_insert_all_liveprops(dav_core_insert_all_liveprops,
                                  NULL, NULL, APR_HOOK_MIDDLE);

    dav_core_register_uris(p);
}
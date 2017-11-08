static void register_hooks(apr_pool_t *p)
{
    dav_hook_gather_propsets(dav_fs_gather_propsets, NULL, NULL,
                             APR_HOOK_MIDDLE);
    dav_hook_find_liveprop(dav_fs_find_liveprop, NULL, NULL, APR_HOOK_MIDDLE);
    dav_hook_insert_all_liveprops(dav_fs_insert_all_liveprops, NULL, NULL,
                                  APR_HOOK_MIDDLE);

    dav_fs_register(p);
}
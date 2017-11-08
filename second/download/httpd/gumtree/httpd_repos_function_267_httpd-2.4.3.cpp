int dav_fs_find_liveprop(const dav_resource *resource,
                         const char *ns_uri, const char *name,
                         const dav_hooks_liveprop **hooks)
{
    /* don't try to find any liveprops if this isn't "our" resource */
    if (resource->hooks != &dav_hooks_repository_fs)
        return 0;
    return dav_do_find_liveprop(ns_uri, name, &dav_fs_liveprop_group, hooks);
}
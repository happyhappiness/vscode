int dav_core_find_liveprop(const dav_resource *resource,
                           const char *ns_uri, const char *name,
                           const dav_hooks_liveprop **hooks)
{
    return dav_do_find_liveprop(ns_uri, name, &dav_core_liveprop_group, hooks);
}
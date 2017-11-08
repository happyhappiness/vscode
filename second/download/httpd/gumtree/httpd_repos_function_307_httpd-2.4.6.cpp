static int dav_core_is_writable(const dav_resource *resource, int propid)
{
    const dav_liveprop_spec *info;

    (void) dav_get_liveprop_info(propid, &dav_core_liveprop_group, &info);
    return info->is_writable;
}
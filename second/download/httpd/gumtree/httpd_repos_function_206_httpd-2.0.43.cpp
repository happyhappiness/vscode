static int dav_fs_is_writable(const dav_resource *resource, int propid)
{
    const dav_liveprop_spec *info;

#ifdef DAV_FS_HAS_EXECUTABLE
    /* if we have the executable property, and this isn't a collection,
       then the property is writable. */
    if (propid == DAV_PROPID_FS_executable && !resource->collection)
	return 1;
#endif

    (void) dav_get_liveprop_info(propid, &dav_fs_liveprop_group, &info);
    return info->is_writable;
}
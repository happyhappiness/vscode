dav_error * dav_fs_get_locknull_members(
    const dav_resource *resource,
    dav_buffer *pbuf)
{
    const char *dirpath;

    /* ### should test this result value... */
    (void) dav_fs_dir_file_name(resource, &dirpath, NULL);
    return dav_fs_load_locknull_list(dav_fs_pool(resource), dirpath, pbuf);
}
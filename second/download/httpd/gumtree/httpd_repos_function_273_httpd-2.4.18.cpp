void dav_fs_gather_propsets(apr_array_header_t *uris)
{
#ifdef DAV_FS_HAS_EXECUTABLE
    *(const char **)apr_array_push(uris) =
        "<http://apache.org/dav/propset/fs/1>";
#endif
}
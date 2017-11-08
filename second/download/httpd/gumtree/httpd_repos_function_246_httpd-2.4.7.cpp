static dav_error * dav_fs_open_stream(const dav_resource *resource,
                                      dav_stream_mode mode,
                                      dav_stream **stream)
{
    apr_pool_t *p = resource->info->pool;
    dav_stream *ds = apr_pcalloc(p, sizeof(*ds));
    apr_int32_t flags;
    apr_status_t rv;

    switch (mode) {
    default:
        flags = APR_READ | APR_BINARY;
        break;

    case DAV_MODE_WRITE_TRUNC:
        flags = APR_WRITE | APR_CREATE | APR_TRUNCATE | APR_BINARY;
        break;
    case DAV_MODE_WRITE_SEEKABLE:
        flags = APR_WRITE | APR_CREATE | APR_BINARY;
        break;
    }

    ds->p = p;
    ds->pathname = resource->info->pathname;
    ds->temppath = NULL;
    ds->unlink_on_error = 0;

    if (mode == DAV_MODE_WRITE_TRUNC) {
        ds->temppath = apr_pstrcat(p, ap_make_dirstr_parent(p, ds->pathname),
                                   DAV_FS_TMP_PREFIX "XXXXXX", NULL);
        rv = dav_fs_mktemp(&ds->f, ds->temppath, ds->p);
        apr_pool_cleanup_register(p, ds, tmpfile_cleanup,
                                  apr_pool_cleanup_null);
    }
    else if (mode == DAV_MODE_WRITE_SEEKABLE) {
        rv = apr_file_open(&ds->f, ds->pathname, flags | APR_FOPEN_EXCL,
                           APR_OS_DEFAULT, ds->p);
        if (rv == APR_SUCCESS) {
            /* we have created a new file */
            ds->unlink_on_error = 1;
        }
        else if (APR_STATUS_IS_EEXIST(rv)) {
            rv = apr_file_open(&ds->f, ds->pathname, flags, APR_OS_DEFAULT,
                               ds->p);
        }
    }
    else {
        rv = apr_file_open(&ds->f, ds->pathname, flags, APR_OS_DEFAULT, ds->p);
    }

    if (rv != APR_SUCCESS) {
        return dav_new_error(p, MAP_IO2HTTP(rv), 0, rv,
                             "An error occurred while opening a resource.");
    }

    /* (APR registers cleanups for the fd with the pool) */

    *stream = ds;
    return NULL;
}
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
    rv = apr_file_open(&ds->f, ds->pathname, flags, APR_OS_DEFAULT, ds->p);
    if (rv != APR_SUCCESS) {
        return dav_new_error(p, MAP_IO2HTTP(rv), 0,
                             "An error occurred while opening a resource.");
    }

    /* (APR registers cleanups for the fd with the pool) */

    *stream = ds;
    return NULL;
}
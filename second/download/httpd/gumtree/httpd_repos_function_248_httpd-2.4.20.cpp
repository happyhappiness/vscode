static apr_status_t tmpfile_cleanup(void *data)
{
    dav_stream *ds = data;
    if (ds->temppath) {
        apr_file_remove(ds->temppath, ds->p);
    }
    return APR_SUCCESS;
}
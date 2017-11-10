static apr_status_t file_cache_el_final(disk_cache_conf *conf, disk_cache_file_t *file,
                                        request_rec *r)
{
    apr_status_t rv = APR_SUCCESS;

    /* This assumes that the tempfiles are on the same file system
     * as the cache_root. If not, then we need a file copy/move
     * rather than a rename.
     */

    /* move the file over */
    if (file->tempfd) {

        rv = safe_file_rename(conf, file->tempfile, file->file, file->pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00699)
                    "rename tempfile to file failed:"
                    " %s -> %s", file->tempfile, file->file);
            apr_file_remove(file->tempfile, file->pool);
        }

        file->tempfd = NULL;
    }

    return rv;
}
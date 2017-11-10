static dav_error * dav_fs_save_locknull_list(apr_pool_t *p, const char *dirpath,
                                             dav_buffer *pbuf)
{
    const char *pathname;
    apr_file_t *file = NULL;
    dav_error *err = NULL;
    apr_size_t amt;
    apr_status_t rv;

    if (pbuf->buf == NULL)
        return NULL;

    dav_fs_ensure_state_dir(p, dirpath);
    pathname = apr_pstrcat(p,
                          dirpath,
                          dirpath[strlen(dirpath) - 1] == '/' ? "" : "/",
                          DAV_FS_STATE_DIR "/" DAV_FS_LOCK_NULL_FILE,
                          NULL);

    if (pbuf->cur_len == 0) {
        /* delete the file if cur_len == 0 */
        if ((rv = apr_file_remove(pathname, p)) != APR_SUCCESS) {
            return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, rv,
                                 apr_psprintf(p,
                                             "Error removing %s", pathname));
        }
        return NULL;
    }

    if ((rv = apr_file_open(&file, pathname,
                            APR_WRITE | APR_CREATE | APR_TRUNCATE | APR_BINARY,
                            APR_OS_DEFAULT, p)) != APR_SUCCESS) {
        return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, rv,
                             apr_psprintf(p,
                                         "Error opening %s for writing",
                                         pathname));
    }

    amt = pbuf->cur_len;
    if ((rv = apr_file_write_full(file, pbuf->buf, amt, &amt)) != APR_SUCCESS
        || amt != pbuf->cur_len) {
        err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, rv,
                            apr_psprintf(p,
                                        "Error writing %" APR_SIZE_T_FMT
                                        " bytes to %s",
                                        pbuf->cur_len, pathname));
    }

    apr_file_close(file);
    return err;
}
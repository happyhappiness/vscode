static dav_error * dav_fs_load_locknull_list(apr_pool_t *p, const char *dirpath,
                                             dav_buffer *pbuf)
{
    apr_finfo_t finfo;
    apr_file_t *file = NULL;
    dav_error *err = NULL;
    apr_size_t amt;
    apr_status_t rv;

    dav_buffer_init(p, pbuf, dirpath);

    if (pbuf->buf[pbuf->cur_len - 1] == '/')
        pbuf->buf[--pbuf->cur_len] = '\0';

    dav_buffer_place(p, pbuf, "/" DAV_FS_STATE_DIR "/" DAV_FS_LOCK_NULL_FILE);

    /* reset this in case we leave w/o reading into the buffer */
    pbuf->cur_len = 0;

    if (apr_file_open(&file, pbuf->buf, APR_READ | APR_BINARY, APR_OS_DEFAULT,
                p) != APR_SUCCESS) {
        return NULL;
    }

    rv = apr_file_info_get(&finfo, APR_FINFO_SIZE, file);
    if (rv != APR_SUCCESS) {
        err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, rv,
                            apr_psprintf(p,
                                        "Opened but could not stat file %s",
                                        pbuf->buf));
        goto loaderror;
    }

    if (finfo.size != (apr_size_t)finfo.size) {
        err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, 0,
                            apr_psprintf(p,
                                        "Opened but rejected huge file %s",
                                        pbuf->buf));
        goto loaderror;
    }

    amt = (apr_size_t)finfo.size;
    dav_set_bufsize(p, pbuf, amt);
    if ((rv = apr_file_read(file, pbuf->buf, &amt)) != APR_SUCCESS
        || amt != finfo.size) {
        err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, rv,
                            apr_psprintf(p,
                                        "Failure reading locknull file "
                                        "for %s", dirpath));

        /* just in case the caller disregards the returned error */
        pbuf->cur_len = 0;
        goto loaderror;
    }

  loaderror:
    apr_file_close(file);
    return err;
}
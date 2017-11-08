static dav_error * dav_fs_copymove_file(
    int is_move,
    apr_pool_t * p,
    const char *src,
    const char *dst,
    const apr_finfo_t *src_finfo,
    const apr_finfo_t *dst_finfo,
    dav_buffer *pbuf)
{
    dav_buffer work_buf = { 0 };
    apr_file_t *inf = NULL;
    apr_file_t *outf = NULL;
    apr_status_t status;
    apr_fileperms_t perms;

    if (pbuf == NULL)
        pbuf = &work_buf;

    /* Determine permissions to use for destination */
    if (src_finfo && src_finfo->valid & APR_FINFO_PROT
        && src_finfo->protection & APR_UEXECUTE) {
        perms = src_finfo->protection;

        if (dst_finfo != NULL) {
            /* chmod it if it already exist */
            if ((status = apr_file_perms_set(dst, perms)) != APR_SUCCESS) {
                return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, status,
                                     "Could not set permissions on destination");
            }
        }
    }
    else {
        perms = APR_OS_DEFAULT;
    }

    dav_set_bufsize(p, pbuf, DAV_FS_COPY_BLOCKSIZE);

    if ((status = apr_file_open(&inf, src, APR_READ | APR_BINARY,
                                APR_OS_DEFAULT, p)) != APR_SUCCESS) {
        /* ### use something besides 500? */
        return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, status,
                             "Could not open file for reading");
    }

    /* ### do we need to deal with the umask? */
    status = apr_file_open(&outf, dst, APR_WRITE | APR_CREATE | APR_TRUNCATE
                           | APR_BINARY, perms, p);
    if (status != APR_SUCCESS) {
        apr_file_close(inf);

        return dav_new_error(p, MAP_IO2HTTP(status), 0, status,
                             "Could not open file for writing");
    }

    while (1) {
        apr_size_t len = DAV_FS_COPY_BLOCKSIZE;

        status = apr_file_read(inf, pbuf->buf, &len);
        if (status != APR_SUCCESS && status != APR_EOF) {
            apr_status_t lcl_status;

            apr_file_close(inf);
            apr_file_close(outf);

            if ((lcl_status = apr_file_remove(dst, p)) != APR_SUCCESS) {
                /* ### ACK! Inconsistent state... */

                /* ### use something besides 500? */
                return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                                     lcl_status,
                                     "Could not delete output after read "
                                     "failure. Server is now in an "
                                     "inconsistent state.");
            }

            /* ### use something besides 500? */
            return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, status,
                                 "Could not read input file");
        }

        if (status == APR_EOF)
            break;

        /* write any bytes that were read */
        status = apr_file_write_full(outf, pbuf->buf, len, NULL);
        if (status != APR_SUCCESS) {
            apr_status_t lcl_status;

            apr_file_close(inf);
            apr_file_close(outf);

            if ((lcl_status = apr_file_remove(dst, p)) != APR_SUCCESS) {
                /* ### ACK! Inconsistent state... */

                /* ### use something besides 500? */
                return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                                     lcl_status,
                                     "Could not delete output after write "
                                     "failure. Server is now in an "
                                     "inconsistent state.");
            }

            return dav_new_error(p, MAP_IO2HTTP(status), 0, status,
                                 "Could not write output file");
        }
    }

    apr_file_close(inf);
    apr_file_close(outf);

    if (is_move && (status = apr_file_remove(src, p)) != APR_SUCCESS) {
        dav_error *err;
        apr_status_t lcl_status;

        if (APR_STATUS_IS_ENOENT(status)) {
            /*
             * Something is wrong here but the result is what we wanted.
             * We definitely should not remove the destination file.
             */
            err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, status,
                                 apr_psprintf(p, "Could not remove source "
                                              "file %s after move to %s. The "
                                              "server may be in an "
                                              "inconsistent state.", src, dst));
            return err;
        }
        else if ((lcl_status = apr_file_remove(dst, p)) != APR_SUCCESS) {
            /* ### ACK. this creates an inconsistency. do more!? */

            /* ### use something besides 500? */
            return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, lcl_status,
                                 "Could not remove source or destination "
                                 "file. Server is now in an inconsistent "
                                 "state.");
        }

        /* ### use something besides 500? */
        err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, status,
                            "Could not remove source file after move. "
                            "Destination was removed to ensure consistency.");
        return err;
    }

    return NULL;
}
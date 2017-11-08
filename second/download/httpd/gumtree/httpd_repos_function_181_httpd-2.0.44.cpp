static dav_error * dav_fs_copymove_file(
    int is_move,
    apr_pool_t * p,
    const char *src,
    const char *dst,
    dav_buffer *pbuf)
{
    dav_buffer work_buf = { 0 };
    apr_file_t *inf = NULL;
    apr_file_t *outf = NULL;

    if (pbuf == NULL)
        pbuf = &work_buf;

    dav_set_bufsize(p, pbuf, DAV_FS_COPY_BLOCKSIZE);

    if ((apr_file_open(&inf, src, APR_READ | APR_BINARY, APR_OS_DEFAULT, p)) 
            != APR_SUCCESS) {
        /* ### use something besides 500? */
        return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                             "Could not open file for reading");
    }

    /* ### do we need to deal with the umask? */
    if ((apr_file_open(&outf, dst, APR_WRITE | APR_CREATE | APR_TRUNCATE | APR_BINARY,
                 APR_OS_DEFAULT, p)) != APR_SUCCESS) {
        apr_file_close(inf);

        /* ### use something besides 500? */
        return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                             "Could not open file for writing");
    }

    while (1) {
        apr_size_t len = DAV_FS_COPY_BLOCKSIZE;
        apr_status_t status;

        status = apr_file_read(inf, pbuf->buf, &len);
        if (status != APR_SUCCESS && status != APR_EOF) {
            apr_file_close(inf);
            apr_file_close(outf);
            
            if (apr_file_remove(dst, p) != APR_SUCCESS) {
                /* ### ACK! Inconsistent state... */

                /* ### use something besides 500? */
                return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                                     "Could not delete output after read "
                                     "failure. Server is now in an "
                                     "inconsistent state.");
            }

            /* ### use something besides 500? */
            return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                                 "Could not read input file");
        }

        /* write any bytes that were read (applies to APR_EOF, too) */
        if (apr_file_write_full(outf, pbuf->buf, len, NULL) != APR_SUCCESS) {
            int save_errno = errno;

            apr_file_close(inf);
            apr_file_close(outf);

            if (apr_file_remove(dst, p) != APR_SUCCESS) {
                /* ### ACK! Inconsistent state... */

                /* ### use something besides 500? */
                return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                                     "Could not delete output after write "
                                     "failure. Server is now in an "
                                     "inconsistent state.");
            }

            if (save_errno == ENOSPC) {
                return dav_new_error(p, HTTP_INSUFFICIENT_STORAGE, 0,
                                     "There is not enough storage to write to "
                                     "this resource.");
            }

            /* ### use something besides 500? */
            return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                                 "Could not write output file");
        }

        if (status == APR_EOF)
            break;
    }

    apr_file_close(inf);
    apr_file_close(outf);

    if (is_move && apr_file_remove(src, p) != APR_SUCCESS) {
        dav_error *err;
        int save_errno = errno;   /* save the errno that got us here */

        if (apr_file_remove(dst, p) != APR_SUCCESS) {
            /* ### ACK. this creates an inconsistency. do more!? */

            /* ### use something besides 500? */
            /* Note that we use the latest errno */
            return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                                 "Could not remove source or destination "
                                 "file. Server is now in an inconsistent "
                                 "state.");
        }

        /* ### use something besides 500? */
        err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                            "Could not remove source file after move. "
                            "Destination was removed to ensure consistency.");
        err->save_errno = save_errno;
        return err;
    }

    return NULL;
}
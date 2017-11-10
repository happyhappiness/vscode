static dav_error * dav_fs_copymove_state(
    int is_move,
    apr_pool_t * p,
    const char *src_dir, const char *src_file,
    const char *dst_dir, const char *dst_file,
    dav_buffer *pbuf)
{
    apr_finfo_t src_finfo;        /* finfo for source file */
    apr_finfo_t dst_state_finfo;        /* finfo for STATE directory */
    apr_status_t rv;
    const char *src;
    const char *dst;

    /* build the propset pathname for the source file */
    src = apr_pstrcat(p, src_dir, "/" DAV_FS_STATE_DIR "/", src_file, NULL);

    /* the source file doesn't exist */
    rv = apr_stat(&src_finfo, src, APR_FINFO_NORM, p);
    if (rv != APR_SUCCESS && rv != APR_INCOMPLETE) {
        return NULL;
    }

    /* build the pathname for the destination state dir */
    dst = apr_pstrcat(p, dst_dir, "/" DAV_FS_STATE_DIR, NULL);

    /* ### do we need to deal with the umask? */

    /* ensure that it exists */
    rv = apr_dir_make(dst, APR_OS_DEFAULT, p);
    if (rv != APR_SUCCESS) {
        if (!APR_STATUS_IS_EEXIST(rv)) {
            /* ### use something besides 500? */
            return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, rv,
                                 "Could not create internal state directory");
        }
    }

    /* get info about the state directory */
    rv = apr_stat(&dst_state_finfo, dst, APR_FINFO_NORM, p);
    if (rv != APR_SUCCESS && rv != APR_INCOMPLETE) {
        /* Ack! Where'd it go? */
        /* ### use something besides 500? */
        return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, rv,
                             "State directory disappeared");
    }

    /* The mkdir() may have failed because a *file* exists there already */
    if (dst_state_finfo.filetype != APR_DIR) {
        /* ### try to recover by deleting this file? (and mkdir again) */
        /* ### use something besides 500? */
        return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, 0,
                             "State directory is actually a file");
    }

    /* append the target file to the state directory pathname */
    dst = apr_pstrcat(p, dst, "/", dst_file, NULL);

    /* copy/move the file now */
    if (is_move) {
        /* try simple rename first */
        rv = apr_file_rename(src, dst, p);
        if (APR_STATUS_IS_EXDEV(rv)) {
            return dav_fs_copymove_file(is_move, p, src, dst, NULL, NULL, pbuf);
        }
        if (rv != APR_SUCCESS) {
            /* ### use something besides 500? */
            return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, rv,
                                 "Could not move state file.");
        }
    }
    else
    {
        /* gotta copy (and delete) */
        return dav_fs_copymove_file(is_move, p, src, dst, NULL, NULL, pbuf);
    }

    return NULL;
}
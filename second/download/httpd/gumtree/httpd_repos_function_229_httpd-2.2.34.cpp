static dav_error *dav_fs_copymoveset(int is_move, apr_pool_t *p,
                                     const dav_resource *src,
                                     const dav_resource *dst,
                                     dav_buffer *pbuf)
{
    const char *src_dir;
    const char *src_file;
    const char *src_state1;
    const char *src_state2;
    const char *dst_dir;
    const char *dst_file;
    const char *dst_state1;
    const char *dst_state2;
    dav_error *err;

    /* Get directory and filename for resources */
    /* ### should test these result values... */
    (void) dav_fs_dir_file_name(src, &src_dir, &src_file);
    (void) dav_fs_dir_file_name(dst, &dst_dir, &dst_file);

    /* Get the corresponding state files for each resource */
    dav_dbm_get_statefiles(p, src_file, &src_state1, &src_state2);
    dav_dbm_get_statefiles(p, dst_file, &dst_state1, &dst_state2);
#if DAV_DEBUG
    if ((src_state2 != NULL && dst_state2 == NULL) ||
        (src_state2 == NULL && dst_state2 != NULL)) {
        return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0,
                             "DESIGN ERROR: dav_dbm_get_statefiles() "
                             "returned inconsistent results.");
    }
#endif

    err = dav_fs_copymove_state(is_move, p,
                                src_dir, src_state1,
                                dst_dir, dst_state1,
                                pbuf);

    if (err == NULL && src_state2 != NULL) {
        err = dav_fs_copymove_state(is_move, p,
                                    src_dir, src_state2,
                                    dst_dir, dst_state2,
                                    pbuf);

        if (err != NULL) {
            /* ### CRAP. inconsistency. */
            /* ### should perform some cleanup at the target if we still
               ### have the original files */

            /* Change the error to reflect the bad server state. */
            err->status = HTTP_INTERNAL_SERVER_ERROR;
            err->desc =
                "Could not fully copy/move the properties. "
                "The server is now in an inconsistent state.";
        }
    }

    return err;
}
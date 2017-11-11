static dav_error *dav_fs_copymove_resource(
    int is_move,
    const dav_resource *src,
    const dav_resource *dst,
    int depth,
    dav_response **response)
{
    dav_error *err = NULL;
    dav_buffer work_buf = { 0 };

    *response = NULL;

    /* if a collection, recursively copy/move it and its children,
     * including the state dirs
     */
    if (src->collection) {
        dav_walk_params params = { 0 };
        dav_response *multi_status;

        params.walk_type = DAV_WALKTYPE_NORMAL | DAV_WALKTYPE_HIDDEN;
        params.func = dav_fs_copymove_walker;
        params.pool = src->info->pool;
        params.root = src;

        /* params.walk_ctx is managed by dav_fs_internal_walk() */

        /* postfix is needed for MOVE to delete source dirs */
        if (is_move)
            params.walk_type |= DAV_WALKTYPE_POSTFIX;

        /* note that we return the error OR the multistatus. never both */

        if ((err = dav_fs_internal_walk(&params, depth, is_move, dst,
                                        &multi_status)) != NULL) {
            /* on a "real" error, then just punt. nothing else to do. */
            return err;
        }

        if ((*response = multi_status) != NULL) {
            /* some multistatus responses exist. wrap them in a 207 */
            return dav_new_error(src->info->pool, HTTP_MULTI_STATUS, 0, 0,
                                 "Error(s) occurred on some resources during "
                                 "the COPY/MOVE process.");
        }

        return NULL;
    }

    /* not a collection */
    if ((err = dav_fs_copymove_file(is_move, src->info->pool,
                                    src->info->pathname, dst->info->pathname,
                                    &src->info->finfo,
                                    dst->exists ? &dst->info->finfo : NULL,
                                    &work_buf)) != NULL) {
        /* ### push a higher-level description? */
        return err;
    }

    /* copy/move properties as well */
    return dav_fs_copymoveset(is_move, src->info->pool, src, dst, &work_buf);
}
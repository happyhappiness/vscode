static dav_error * dav_fs_copy_resource(
    const dav_resource *src,
    dav_resource *dst,
    int depth,
    dav_response **response)
{
    dav_error *err;

#if DAV_DEBUG
    if (src->hooks != dst->hooks) {
        /*
        ** ### strictly speaking, this is a design error; we should not
        ** ### have reached this point.
        */
        return dav_new_error(src->info->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                             "DESIGN ERROR: a mix of repositories "
                             "was passed to copy_resource.");
    }
#endif

    if ((err = dav_fs_copymove_resource(0, src, dst, depth,
                                        response)) == NULL) {

        /* update state of destination resource to show it exists */
        dst->exists = 1;
        dst->collection = src->collection;
    }

    return err;
}
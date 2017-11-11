static dav_error * dav_fs_walk(const dav_walk_params *params, int depth,
                               dav_response **response)
{
    /* always return the error, and any/all multistatus responses */
    return dav_fs_internal_walk(params, depth, 0, NULL, response);
}
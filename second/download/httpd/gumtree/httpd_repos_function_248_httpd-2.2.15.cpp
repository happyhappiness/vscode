static dav_error * dav_fs_internal_walk(const dav_walk_params *params,
                                        int depth, int is_move,
                                        const dav_resource *root_dst,
                                        dav_response **response)
{
    dav_fs_walker_context fsctx = { 0 };
    dav_error *err;
    dav_fs_copymove_walk_ctx cm_ctx = { 0 };

#if DAV_DEBUG
    if ((params->walk_type & DAV_WALKTYPE_LOCKNULL) != 0
        && params->lockdb == NULL) {
        return dav_new_error(params->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                             "DESIGN ERROR: walker called to walk locknull "
                             "resources, but a lockdb was not provided.");
    }
#endif

    fsctx.params = params;
    fsctx.wres.walk_ctx = params->walk_ctx;
    fsctx.wres.pool = params->pool;

    /* ### zero out versioned, working, baselined? */

    fsctx.res1 = *params->root;
    fsctx.res1.pool = params->pool;

    fsctx.res1.info = &fsctx.info1;
    fsctx.info1 = *params->root->info;

    /* the pathname is stored in the path1 buffer */
    dav_buffer_init(params->pool, &fsctx.path1, fsctx.info1.pathname);
    fsctx.info1.pathname = fsctx.path1.buf;

    if (root_dst != NULL) {
        /* internal call from the COPY/MOVE code. set it up. */

        fsctx.wres.walk_ctx = &cm_ctx;
        cm_ctx.is_move = is_move;
        cm_ctx.res_dst = &fsctx.res2;
        cm_ctx.root = params->root;
        cm_ctx.pool = params->pool;

        fsctx.res2 = *root_dst;
        fsctx.res2.exists = 0;
        fsctx.res2.collection = 0;
        fsctx.res2.uri = NULL;          /* we don't track this */
        fsctx.res2.pool = params->pool;

        fsctx.res2.info = &fsctx.info2;
        fsctx.info2 = *root_dst->info;

        /* res2 does not exist -- clear its finfo structure */
        memset(&fsctx.info2.finfo, 0, sizeof(fsctx.info2.finfo));

        /* the pathname is stored in the path2 buffer */
        dav_buffer_init(params->pool, &fsctx.path2, fsctx.info2.pathname);
        fsctx.info2.pathname = fsctx.path2.buf;
    }

    /* prep the URI buffer */
    dav_buffer_init(params->pool, &fsctx.uri_buf, params->root->uri);

    /* if we have a directory, then ensure the URI has a trailing "/" */
    if (fsctx.res1.collection
        && fsctx.uri_buf.buf[fsctx.uri_buf.cur_len - 1] != '/') {

        /* this will fall into the pad area */
        fsctx.uri_buf.buf[fsctx.uri_buf.cur_len++] = '/';
        fsctx.uri_buf.buf[fsctx.uri_buf.cur_len] = '\0';
    }

    /* the current resource's URI is stored in the uri_buf buffer */
    fsctx.res1.uri = fsctx.uri_buf.buf;

    /* point the callback's resource at our structure */
    fsctx.wres.resource = &fsctx.res1;

    /* always return the error, and any/all multistatus responses */
    err = dav_fs_walker(&fsctx, depth);
    *response = fsctx.wres.response;
    return err;
}
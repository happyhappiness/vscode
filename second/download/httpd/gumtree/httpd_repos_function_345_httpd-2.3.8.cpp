static void dav_stream_response(dav_walk_resource *wres,
                                int status,
                                dav_get_props_result *propstats,
                                apr_pool_t *pool)
{
    dav_response resp = { 0 };
    dav_walker_ctx *ctx = wres->walk_ctx;

    resp.href = wres->resource->uri;
    resp.status = status;
    if (propstats) {
        resp.propresult = *propstats;
    }

    dav_send_one_response(&resp, ctx->bb, ctx->r->output_filters, pool);
}
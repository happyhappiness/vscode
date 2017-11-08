apr_status_t h2_stream_readx(h2_stream *stream, 
                             h2_io_data_cb *cb, void *ctx,
                             apr_size_t *plen, int *peos)
{
    if (stream->bbout && !APR_BRIGADE_EMPTY(stream->bbout)) {
        return h2_util_bb_readx(stream->bbout, cb, ctx, plen, peos);
    }
    return h2_mplx_out_readx(stream->m, stream->id, 
                             cb, ctx, plen, peos);
}
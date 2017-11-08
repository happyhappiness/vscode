apr_status_t h2_stream_readx(h2_stream *stream, 
                             h2_io_data_cb *cb, void *ctx,
                             apr_off_t *plen, int *peos)
{
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    if (!stream->sos) {
        return APR_EGENERAL;
    }
    return stream->sos->readx(stream->sos, cb, ctx, plen, peos);
}
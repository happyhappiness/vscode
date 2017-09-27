int h2_stream_is_suspended(const h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    return stream->suspended;
}

apr_status_t h2_stream_out_prepare(h2_stream *stream, 
                                   apr_off_t *plen, int *peos)
{
    if (stream->rst_error) {
        *plen = 0;
        *peos = 1;
        return APR_ECONNRESET;
    }

    AP_DEBUG_ASSERT(stream->sos);
    return stream->sos->prepare(stream->sos, plen, peos);
}

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

apr_status_t h2_stream_read_to(h2_stream *stream, apr_bucket_brigade *bb, 
                               apr_off_t *plen, int *peos)
{
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    if (!stream->sos) {
        return APR_EGENERAL;
    }
    return stream->sos->read_to(stream->sos, bb, plen, peos);
}

int h2_stream_input_is_open(const h2_stream *stream) 
{
    return input_open(stream);
}

int h2_stream_needs_submit(const h2_stream *stream)

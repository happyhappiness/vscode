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
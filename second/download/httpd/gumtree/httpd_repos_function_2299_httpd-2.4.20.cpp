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
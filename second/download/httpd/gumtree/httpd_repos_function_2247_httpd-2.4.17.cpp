apr_status_t h2_stream_write_data(h2_stream *stream,
                                  const char *data, size_t len)
{
    AP_DEBUG_ASSERT(stream);
    AP_DEBUG_ASSERT(stream);
    switch (stream->state) {
        case H2_STREAM_ST_OPEN:
            break;
        default:
            return APR_EINVAL;
    }
    return h2_request_write_data(stream->request, data, len);
}
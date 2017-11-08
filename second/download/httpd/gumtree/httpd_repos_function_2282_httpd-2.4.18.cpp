static apr_status_t input_add_data(h2_stream *stream,
                                   const char *data, size_t len, int chunked)
{
    apr_status_t status = APR_SUCCESS;
    
    if (chunked) {
        status = apr_brigade_printf(stream->bbin, input_flush, stream,
                                    "%lx\r\n", (unsigned long)len);
        if (status == APR_SUCCESS) {
            status = apr_brigade_write(stream->bbin, input_flush, stream, data, len);
            if (status == APR_SUCCESS) {
                status = apr_brigade_puts(stream->bbin, input_flush, stream, "\r\n");
            }
        }
    }
    else {
        status = apr_brigade_write(stream->bbin, input_flush, stream, data, len);
    }
    return status;
}
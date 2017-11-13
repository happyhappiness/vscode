apr_status_t h2_stream_close_input(h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    
    AP_DEBUG_ASSERT(stream);
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
                  "h2_stream(%ld-%d): closing input",
                  stream->session->id, stream->id);
                  
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    
    H2_STREAM_IN(APLOG_TRACE2, stream, "close_pre");
    if (close_input(stream) && stream->bbin) {
        if (stream->request->chunked) {
            apr_table_t *trailers = stream->request->trailers;
            if (trailers && !apr_is_empty_table(trailers)) {
                status = input_add_data(stream, "0\r\n", 3, 0);
                apr_table_do(input_add_header, stream, trailers, NULL);
                status = input_add_data(stream, "\r\n", 2, 0);
            }
            else {
                status = input_add_data(stream, "0\r\n\r\n", 5, 0);
            }
        }
        
        if (status == APR_SUCCESS) {
            status = h2_stream_input_flush(stream);
        }
        if (status == APR_SUCCESS) {
            status = h2_mplx_in_close(stream->session->mplx, stream->id);
        }
    }
    H2_STREAM_IN(APLOG_TRACE2, stream, "close_post");
    return status;
}
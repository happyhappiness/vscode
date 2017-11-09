static void set_error_response(h2_stream *stream, int http_status)
{
    if (!h2_stream_is_ready(stream)) {
        conn_rec *c = stream->session->c;
        apr_bucket *b;
        h2_headers *response;
        
        response = h2_headers_die(http_status, stream->request, stream->pool);
        prep_output(stream);
        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_HEAD(stream->out_buffer, b);
        b = h2_bucket_headers_create(c->bucket_alloc, response);
        APR_BRIGADE_INSERT_HEAD(stream->out_buffer, b);
    }
}
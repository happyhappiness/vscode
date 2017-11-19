static void ev_stream_done(h2_proxy_session *session, int stream_id, 
                           const char *msg)
{
    h2_proxy_stream *stream;
    
    stream = nghttp2_session_get_stream_user_data(session->ngh2, stream_id);
    if (stream) {
        int touched = (stream->data_sent || 
                       stream_id <= session->last_stream_id);
        int complete = (stream->error_code == 0);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03364)
                      "h2_proxy_sesssion(%s): stream(%d) closed "
                      "(complete=%d, touched=%d)", 
                      session->id, stream_id, complete, touched);
        
        if (complete && !stream->data_received) {
            apr_bucket *b;
            /* if the response had no body, this is the time to flush
             * an empty brigade which will also "write" the resonse
             * headers */
            h2_proxy_stream_end_headers_out(stream);
            stream->data_received = 1;
            b = apr_bucket_flush_create(stream->r->connection->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(stream->output, b);
            b = apr_bucket_eos_create(stream->r->connection->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(stream->output, b);
            ap_pass_brigade(stream->r->output_filters, stream->output);
        }
        
        stream->state = H2_STREAM_ST_CLOSED;
        h2_ihash_remove(session->streams, stream_id);
        h2_iq_remove(session->suspended, stream_id);
        if (session->done) {
            session->done(session, stream->r, complete, touched);
        }
    }
    
    switch (session->state) {
        default:
            /* nop */
            break;
    }
}
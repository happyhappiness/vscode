    }
    status = h2_append_brigade(bb, stream->out_buffer, plen, peos, is_not_headers);
    if (status == APR_SUCCESS && !*peos && !*plen) {
        status = APR_EAGAIN;
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, c,
                  "h2_stream(%ld-%d): read_to, len=%ld eos=%d",
                  c->id, stream->id, (long)*plen, *peos);
    return status;
}


int h2_stream_input_is_open(const h2_stream *stream) 
{
    return input_open(stream);
}

apr_status_t h2_stream_submit_pushes(h2_stream *stream, h2_headers *response)
{
    apr_status_t status = APR_SUCCESS;
    apr_array_header_t *pushes;
    int i;
    
    pushes = h2_push_collect_update(stream, stream->request, response);
    if (pushes && !apr_is_empty_array(pushes)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): found %d push candidates",
                      stream->session->id, stream->id, pushes->nelts);
        for (i = 0; i < pushes->nelts; ++i) {
            h2_push *push = APR_ARRAY_IDX(pushes, i, h2_push*);
            h2_stream *s = h2_session_push(stream->session, stream, push);
            if (!s) {
                status = APR_ECONNRESET;
                break;

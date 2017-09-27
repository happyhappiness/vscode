apr_status_t h2_stream_submit_pushes(h2_stream *stream)
{
    apr_status_t status = APR_SUCCESS;
    apr_array_header_t *pushes;
    int i;
    
    pushes = h2_push_collect(stream->pool, stream->request, stream->response);
    if (pushes && !apr_is_empty_array(pushes)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): found %d push candidates",
                      stream->session->id, stream->id, pushes->nelts);
        for (i = 0; i < pushes->nelts; ++i) {
            h2_push *push = APR_ARRAY_IDX(pushes, i, h2_push*);

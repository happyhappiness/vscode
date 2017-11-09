static apr_status_t h2_status_insert(h2_task *task, apr_bucket *b)
{
    conn_rec *c = task->c->master;
    h2_ctx *h2ctx = h2_ctx_get(c, 0);
    h2_session *session;
    h2_stream *stream;
    apr_bucket_brigade *bb;
    apr_bucket *e;
    int32_t connFlowIn, connFlowOut;
    
    
    if (!h2ctx || (session = h2_ctx_session_get(h2ctx)) == NULL) {
        return APR_SUCCESS;
    }
    
    stream = h2_session_stream_get(session, task->stream_id);
    if (!stream) {
        /* stream already done */
        return APR_SUCCESS;
    }
    
    bb = apr_brigade_create(stream->pool, c->bucket_alloc);
    
    connFlowIn = nghttp2_session_get_effective_local_window_size(session->ngh2); 
    connFlowOut = nghttp2_session_get_remote_window_size(session->ngh2);
     
    bbout(bb, "{\n");
    bbout(bb, "  \"version\": \"draft-01\",\n");
    add_settings(bb, session, 0);
    add_peer_settings(bb, session, 0);
    bbout(bb, "  \"connFlowIn\": %d,\n", connFlowIn);
    bbout(bb, "  \"connFlowOut\": %d,\n", connFlowOut);
    bbout(bb, "  \"sentGoAway\": %d,\n", session->local.shutdown);

    add_streams(bb, session, 0);
    
    add_stats(bb, session, stream, 1);
    bbout(bb, "}\n");
    
    while ((e = APR_BRIGADE_FIRST(bb)) != APR_BRIGADE_SENTINEL(bb)) {
        APR_BUCKET_REMOVE(e);
        APR_BUCKET_INSERT_AFTER(b, e);
        b = e;
    }
    apr_brigade_destroy(bb);
    
    return APR_SUCCESS;
}
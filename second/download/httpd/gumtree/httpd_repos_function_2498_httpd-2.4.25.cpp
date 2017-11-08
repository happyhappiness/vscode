static apr_status_t h2_status_insert(h2_task *task, apr_bucket *b)
{
    h2_mplx *m = task->mplx;
    h2_stream *stream = h2_mplx_stream_get(m, task->stream_id);
    h2_session *s;
    conn_rec *c;
    
    apr_bucket_brigade *bb;
    apr_bucket *e;
    int32_t connFlowIn, connFlowOut;
    
    if (!stream) {
        /* stream already done */
        return APR_SUCCESS;
    }
    s = stream->session;
    c = s->c;
    
    bb = apr_brigade_create(stream->pool, c->bucket_alloc);
    
    connFlowIn = nghttp2_session_get_effective_local_window_size(s->ngh2); 
    connFlowOut = nghttp2_session_get_remote_window_size(s->ngh2);
     
    bbout(bb, "{\n");
    bbout(bb, "  \"version\": \"draft-01\",\n");
    add_settings(bb, s, 0);
    add_peer_settings(bb, s, 0);
    bbout(bb, "  \"connFlowIn\": %d,\n", connFlowIn);
    bbout(bb, "  \"connFlowOut\": %d,\n", connFlowOut);
    bbout(bb, "  \"sentGoAway\": %d,\n", s->local.shutdown);

    add_streams(bb, s, 0);
    
    add_stats(bb, s, stream, 1);
    bbout(bb, "}\n");
    
    while ((e = APR_BRIGADE_FIRST(bb)) != APR_BRIGADE_SENTINEL(bb)) {
        APR_BUCKET_REMOVE(e);
        APR_BUCKET_INSERT_AFTER(b, e);
        b = e;
    }
    apr_brigade_destroy(bb);
    
    return APR_SUCCESS;
}
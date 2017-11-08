apr_array_header_t *h2_push_collect_update(h2_stream *stream, 
                                           const struct h2_request *req, 
                                           const struct h2_response *res)
{
    h2_session *session = stream->session;
    const char *cache_digest = apr_table_get(req->headers, "Cache-Digest");
    apr_array_header_t *pushes;
    apr_status_t status;
    
    if (cache_digest && session->push_diary) {
        status = h2_push_diary_digest64_set(session->push_diary, req->authority, 
                                            cache_digest, stream->pool);
        if (status != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                          APLOGNO(03057)
                          "h2_session(%ld): push diary set from Cache-Digest: %s", 
                          session->id, cache_digest);
        }
    }
    pushes = h2_push_collect(stream->pool, req, res);
    return h2_push_diary_update(stream->session, pushes);
}
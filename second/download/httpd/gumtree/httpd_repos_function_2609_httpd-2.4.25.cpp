apr_status_t h2_proxy_session_submit(h2_proxy_session *session, 
                                     const char *url, request_rec *r,
                                     int standalone)
{
    h2_proxy_stream *stream;
    apr_status_t status;
    
    status = open_stream(session, url, r, standalone, &stream);
    if (status == APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03381)
                      "process stream(%d): %s %s%s, original: %s", 
                      stream->id, stream->req->method, 
                      stream->req->authority, stream->req->path, 
                      r->the_request);
        status = submit_stream(session, stream);
    }
    return status;
}
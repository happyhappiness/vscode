static int submit_response(h2_session *session, h2_response *response)
{
    nghttp2_data_provider provider;
    int rv;
    
    memset(&provider, 0, sizeof(provider));
    provider.source.fd = response->stream_id;
    provider.read_callback = stream_data_cb;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "h2_stream(%ld-%d): submitting response %s",
                  session->id, response->stream_id, response->status);
    
    rv = nghttp2_submit_response(session->ngh2, response->stream_id,
                                 response->ngheader->nv, 
                                 response->ngheader->nvlen, &provider);
    
    if (rv != 0) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02939) "h2_stream(%ld-%d): submit_response: %s",
                      session->id, response->stream_id, nghttp2_strerror(rv));
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): submitted response %s, rv=%d",
                      session->id, response->stream_id, 
                      response->status, rv);
    }
    return rv;
}
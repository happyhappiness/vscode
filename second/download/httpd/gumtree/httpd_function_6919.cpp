apr_status_t h2_stream_schedule(h2_stream *stream, int eos, int push_enabled, 
                                h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status = APR_EINVAL;
    ap_assert(stream);
    ap_assert(stream->session);
    ap_assert(stream->session->mplx);
    
    if (!stream->scheduled) {
        if (eos) {
            close_input(stream);
        }

        if (h2_stream_is_ready(stream)) {
            /* already have a resonse, probably a HTTP error code */
            return h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
        }
        else if (!stream->request && stream->rtmp) {
            /* This is the common case: a h2_request was being assembled, now
             * it gets finalized and checked for completness */
            status = h2_request_end_headers(stream->rtmp, stream->pool, eos);
            if (status == APR_SUCCESS) {
                stream->rtmp->serialize = h2_config_geti(stream->session->config,
                                                         H2_CONF_SER_HEADERS); 

                stream->request = stream->rtmp;
                stream->rtmp = NULL;
                stream->scheduled = 1;
                
                stream->push_policy = h2_push_policy_determine(stream->request->headers, 
                                                               stream->pool, push_enabled);
            
                
                status = h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                              "h2_stream(%ld-%d): scheduled %s %s://%s%s "
                              "chunked=%d",
                              stream->session->id, stream->id,
                              stream->request->method, stream->request->scheme,
                              stream->request->authority, stream->request->path,
                              stream->request->chunked);
                return status;
            }
        }
        else {
            status = APR_ECONNRESET;
        }
    }
    
    h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                  "h2_stream(%ld-%d): RST=2 (internal err) %s %s://%s%s",
                  stream->session->id, stream->id,
                  stream->request->method, stream->request->scheme,
                  stream->request->authority, stream->request->path);
    return status;
}
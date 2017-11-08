static apr_status_t submit_stream(h2_proxy_session *session, h2_proxy_stream *stream)
{
    h2_proxy_ngheader *hd;
    nghttp2_data_provider *pp = NULL;
    nghttp2_data_provider provider;
    int rv, may_have_request_body = 1;
    apr_status_t status;

    hd = h2_proxy_util_nghd_make_req(stream->pool, stream->req);
    
    /* If we expect a 100-continue response, we must refrain from reading
       any input until we get it. Reading the input will possibly trigger
       HTTP_IN filter to generate the 100-continue itself. */
    if (stream->waiting_on_100 || stream->waiting_on_ping) {
        /* make a small test if we get an EOF/EOS immediately */
        status = ap_get_brigade(stream->r->input_filters, stream->input,
                                AP_MODE_READBYTES, APR_NONBLOCK_READ,
                                APR_BUCKET_BUFF_SIZE);
        may_have_request_body = APR_STATUS_IS_EAGAIN(status)
                                || (status == APR_SUCCESS 
                                    && !APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(stream->input)));
    }
    
    if (may_have_request_body) {
        provider.source.fd = 0;
        provider.source.ptr = NULL;
        provider.read_callback = stream_request_data;
        pp = &provider;
    }

    rv = nghttp2_submit_request(session->ngh2, NULL, 
                                hd->nv, hd->nvlen, pp, stream);
                                
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03363)
                  "h2_proxy_session(%s): submit %s%s -> %d", 
                  session->id, stream->req->authority, stream->req->path,
                  rv);
    if (rv > 0) {
        stream->id = rv;
        stream->state = H2_STREAM_ST_OPEN;
        h2_proxy_ihash_add(session->streams, stream);
        dispatch_event(session, H2_PROXYS_EV_STREAM_SUBMITTED, rv, NULL);
        
        return APR_SUCCESS;
    }
    return APR_EGENERAL;
}
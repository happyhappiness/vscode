static apr_status_t on_stream_headers(h2_session *session, h2_stream *stream,  
                                      h2_headers *headers, apr_off_t len,
                                      int eos)
{
    apr_status_t status = APR_SUCCESS;
    int rv = 0;

    ap_assert(session);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  H2_STRM_MSG(stream, "on_headers"));
    if (headers->status < 100) {
        h2_stream_rst(stream, headers->status);
        goto leave;
    }
    else if (stream->has_response) {
        h2_ngheader *nh;
        
        status = h2_res_create_ngtrailer(&nh, stream->pool, headers);
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c, 
                      H2_STRM_LOG(APLOGNO(03072), stream, "submit %d trailers"), 
                      (int)nh->nvlen);
        if (status == APR_SUCCESS) {
            rv = nghttp2_submit_trailer(session->ngh2, stream->id, 
                                        nh->nv, nh->nvlen);
        }
        else {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                          H2_STRM_LOG(APLOGNO(10024), stream, "invalid trailers"));
            h2_stream_rst(stream, NGHTTP2_PROTOCOL_ERROR);
        }
        goto leave;
    }
    else {
        nghttp2_data_provider provider, *pprovider = NULL;
        h2_ngheader *ngh;
        const char *note;
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                      H2_STRM_LOG(APLOGNO(03073), stream, "submit response %d, REMOTE_WINDOW_SIZE=%u"),
                      headers->status,
                      (unsigned int)nghttp2_session_get_stream_remote_window_size(session->ngh2, stream->id));
        
        if (!eos || len > 0) {
            memset(&provider, 0, sizeof(provider));
            provider.source.fd = stream->id;
            provider.read_callback = stream_data_cb;
            pprovider = &provider;
        }
        
        /* If this stream is not a pushed one itself,
         * and HTTP/2 server push is enabled here,
         * and the response HTTP status is not sth >= 400,
         * and the remote side has pushing enabled,
         * -> find and perform any pushes on this stream
         *    *before* we submit the stream response itself.
         *    This helps clients avoid opening new streams on Link
         *    headers that get pushed right afterwards.
         * 
         * *) the response code is relevant, as we do not want to 
         *    make pushes on 401 or 403 codes and friends. 
         *    And if we see a 304, we do not push either
         *    as the client, having this resource in its cache, might
         *    also have the pushed ones as well.
         */
        if (!stream->initiated_on
            && !stream->has_response
            && stream->request && stream->request->method
            && !strcmp("GET", stream->request->method)
            && (headers->status < 400)
            && (headers->status != 304)
            && h2_session_push_enabled(session)) {
            
            h2_stream_submit_pushes(stream, headers);
        }
        
        if (!stream->pref_priority) {
            stream->pref_priority = h2_stream_get_priority(stream, headers);
        }
        h2_session_set_prio(session, stream, stream->pref_priority);
        
        note = apr_table_get(headers->notes, H2_FILTER_DEBUG_NOTE);
        if (note && !strcmp("on", note)) {
            int32_t connFlowIn, connFlowOut;

            connFlowIn = nghttp2_session_get_effective_local_window_size(session->ngh2); 
            connFlowOut = nghttp2_session_get_remote_window_size(session->ngh2);
            headers = h2_headers_copy(stream->pool, headers);
            apr_table_setn(headers->headers, "conn-flow-in", 
                           apr_itoa(stream->pool, connFlowIn));
            apr_table_setn(headers->headers, "conn-flow-out", 
                           apr_itoa(stream->pool, connFlowOut));
        }
        
        if (headers->status == 103 
            && !h2_config_geti(session->config, H2_CONF_EARLY_HINTS)) {
            /* suppress sending this to the client, it might have triggered 
             * pushes and served its purpose nevertheless */
            rv = 0;
            goto leave;
        }
        
        status = h2_res_create_ngheader(&ngh, stream->pool, headers);
        if (status == APR_SUCCESS) {
            rv = nghttp2_submit_response(session->ngh2, stream->id,
                                         ngh->nv, ngh->nvlen, pprovider);
            stream->has_response = h2_headers_are_response(headers);
            session->have_written = 1;
            
            if (stream->initiated_on) {
                ++session->pushes_submitted;
            }
            else {
                ++session->responses_submitted;
            }
        }
        else {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                          H2_STRM_LOG(APLOGNO(10025), stream, "invalid response"));
            h2_stream_rst(stream, NGHTTP2_PROTOCOL_ERROR);
        }
    }
    
leave:
    if (nghttp2_is_fatal(rv)) {
        status = APR_EGENERAL;
        dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, rv, nghttp2_strerror(rv));
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02940) "submit_response: %s", 
                      nghttp2_strerror(rv));
    }
    
    ++session->unsent_submits;
    
    /* Unsent push promises are written immediately, as nghttp2
     * 1.5.0 realizes internal stream data structures only on 
     * send and we might need them for other submits. 
     * Also, to conserve memory, we send at least every 10 submits
     * so that nghttp2 does not buffer all outbound items too 
     * long.
     */
    if (status == APR_SUCCESS 
        && (session->unsent_promises || session->unsent_submits > 10)) {
        status = h2_session_send(session);
    }
    return status;
}
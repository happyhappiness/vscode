        
        if (!stream->pref_priority) {
            stream->pref_priority = h2_stream_get_priority(stream, headers);
        }
        h2_session_set_prio(session, stream, stream->pref_priority);
        
        hout = headers->headers;
        note = apr_table_get(headers->notes, H2_FILTER_DEBUG_NOTE);
        if (note && !strcmp("on", note)) {
            int32_t connFlowIn, connFlowOut;

            connFlowIn = nghttp2_session_get_effective_local_window_size(session->ngh2); 
            connFlowOut = nghttp2_session_get_remote_window_size(session->ngh2);
            hout = apr_table_clone(stream->pool, hout);
            apr_table_setn(hout, "conn-flow-in", 
                           apr_itoa(stream->pool, connFlowIn));
            apr_table_setn(hout, "conn-flow-out", 
                           apr_itoa(stream->pool, connFlowOut));
        }
        
        if (headers->status == 103 
            && !h2_config_geti(session->config, H2_CONF_EARLY_HINTS)) {
            /* suppress sending this to the client, it might have triggered 
             * pushes and served its purpose nevertheless */
            rv = 0;
            goto leave;
        }
        
        ngh = h2_util_ngheader_make_res(stream->pool, headers->status, hout);
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
    
leave:
    if (nghttp2_is_fatal(rv)) {
        status = APR_EGENERAL;

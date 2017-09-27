        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02937) 
                      "h2_stream(%ld-%d): data requested but stream not found",
                      session->id, (int)stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    AP_DEBUG_ASSERT(!h2_stream_is_suspended(stream));
    
    status = h2_stream_out_prepare(stream, &nread, &eos);
    if (nread) {
        *data_flags |=  NGHTTP2_DATA_FLAG_NO_COPY;
    }
    
    switch (status) {
        case APR_SUCCESS:

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(03361)
                     "h2_proxy_stream(%s): data_read, stream %d not found", 
                     stream->session->id, stream_id);
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    if (APR_BRIGADE_EMPTY(stream->input)) {
        status = ap_get_brigade(stream->r->input_filters, stream->input,
                                AP_MODE_READBYTES, APR_NONBLOCK_READ,
                                H2MAX(APR_BUCKET_BUFF_SIZE, length));
        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, status, stream->r, 
                      "h2_proxy_stream(%s-%d): request body read", 
                      stream->session->id, stream->id);

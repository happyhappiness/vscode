h2_proxy_session *h2_proxy_session_setup(const char *id, proxy_conn_rec *p_conn,
                                         proxy_server_conf *conf,
                                         int h2_front, 
                                         unsigned char window_bits_connection,
                                         unsigned char window_bits_stream,
                                         h2_proxy_request_done *done)
{
    if (!p_conn->data) {
        apr_pool_t *pool = p_conn->scpool;
        h2_proxy_session *session;
        nghttp2_session_callbacks *cbs;
        nghttp2_option *option;

        session = apr_pcalloc(pool, sizeof(*session));
        apr_pool_pre_cleanup_register(pool, p_conn, proxy_session_pre_close);
        p_conn->data = session;
        
        session->id = apr_pstrdup(p_conn->scpool, id);
        session->c = p_conn->connection;
        session->p_conn = p_conn;
        session->conf = conf;
        session->pool = p_conn->scpool;
        session->state = H2_PROXYS_ST_INIT;
        session->h2_front = h2_front;
        session->window_bits_stream = window_bits_stream;
        session->window_bits_connection = window_bits_connection;
        session->streams = h2_proxy_ihash_create(pool, offsetof(h2_proxy_stream, id));
        session->suspended = h2_proxy_iq_create(pool, 5);
        session->done = done;
    
        session->input = apr_brigade_create(session->pool, session->c->bucket_alloc);
        session->output = apr_brigade_create(session->pool, session->c->bucket_alloc);
    
        nghttp2_session_callbacks_new(&cbs);
        nghttp2_session_callbacks_set_on_frame_recv_callback(cbs, on_frame_recv);
        nghttp2_session_callbacks_set_on_data_chunk_recv_callback(cbs, stream_response_data);
        nghttp2_session_callbacks_set_on_stream_close_callback(cbs, on_stream_close);
        nghttp2_session_callbacks_set_on_header_callback(cbs, on_header);
        nghttp2_session_callbacks_set_before_frame_send_callback(cbs, before_frame_send);
        nghttp2_session_callbacks_set_send_callback(cbs, raw_send);
#ifdef H2_NG2_INVALID_HEADER_CB
        nghttp2_session_callbacks_set_on_invalid_header_callback(cbs, on_invalid_header_cb);
#endif
        
        nghttp2_option_new(&option);
        nghttp2_option_set_peer_max_concurrent_streams(option, 100);
        nghttp2_option_set_no_auto_window_update(option, 1);
        
        nghttp2_session_client_new2(&session->ngh2, cbs, session, option);
        
        nghttp2_option_del(option);
        nghttp2_session_callbacks_del(cbs);

        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03362)
                      "setup session for %s", p_conn->hostname);
    }
    else {
        h2_proxy_session *session = p_conn->data;
        apr_interval_time_t age = apr_time_now() - session->last_frame_received;
        if (age > apr_time_from_sec(1)) {
            session->check_ping = 1;
            nghttp2_submit_ping(session->ngh2, 0, (const uint8_t *)"nevergonnagiveyouup");
        }
    }
    return p_conn->data;
}
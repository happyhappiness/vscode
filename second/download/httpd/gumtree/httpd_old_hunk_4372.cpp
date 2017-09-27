    int id;
    apr_pool_t *pool;
    h2_proxy_session *session;

    const char *url;
    request_rec *r;
    h2_request *req;
    int standalone;

    h2_stream_state_t state;
    unsigned int suspended : 1;
    unsigned int data_sent : 1;
    unsigned int data_received : 1;
    uint32_t error_code;

    apr_bucket_brigade *input;
    apr_bucket_brigade *output;
    
    apr_table_t *saves;
} h2_proxy_stream;


static void dispatch_event(h2_proxy_session *session, h2_proxys_event_t ev, 
                           int arg, const char *msg);


static apr_status_t proxy_session_pre_close(void *theconn)
{
    proxy_conn_rec *p_conn = (proxy_conn_rec *)theconn;
    h2_proxy_session *session = p_conn->data;

    if (session && session->ngh2) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
                      "proxy_session(%s): pool cleanup, state=%d, streams=%d",
                      session->id, session->state, 
                      (int)h2_ihash_count(session->streams));
        session->aborted = 1;
        dispatch_event(session, H2_PROXYS_EV_PRE_CLOSE, 0, NULL);
        nghttp2_session_del(session->ngh2);
        session->ngh2 = NULL;
        p_conn->data = NULL;
    }

    int id;
    apr_pool_t *pool;
    h2_proxy_session *session;

    const char *url;
    request_rec *r;
    h2_proxy_request *req;
    const char *real_server_uri;
    const char *p_server_uri;
    int standalone;

    h2_stream_state_t state;
    unsigned int suspended : 1;
    unsigned int waiting_on_100 : 1;
    unsigned int waiting_on_ping : 1;
    uint32_t error_code;

    apr_bucket_brigade *input;
    apr_off_t data_sent;
    apr_bucket_brigade *output;
    apr_off_t data_received;
    
    apr_table_t *saves;
} h2_proxy_stream;


static void dispatch_event(h2_proxy_session *session, h2_proxys_event_t ev, 
                           int arg, const char *msg);
static void ping_arrived(h2_proxy_session *session);
static apr_status_t check_suspended(h2_proxy_session *session);
static void stream_resume(h2_proxy_stream *stream);


static apr_status_t proxy_session_pre_close(void *theconn)
{
    proxy_conn_rec *p_conn = (proxy_conn_rec *)theconn;
    h2_proxy_session *session = p_conn->data;

    if (session && session->ngh2) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
                      "proxy_session(%s): pool cleanup, state=%d, streams=%d",
                      session->id, session->state, 
                      (int)h2_proxy_ihash_count(session->streams));
        session->aborted = 1;
        dispatch_event(session, H2_PROXYS_EV_PRE_CLOSE, 0, NULL);
        nghttp2_session_del(session->ngh2);
        session->ngh2 = NULL;
        p_conn->data = NULL;
    }

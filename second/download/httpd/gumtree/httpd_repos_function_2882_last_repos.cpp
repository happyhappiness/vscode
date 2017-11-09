static void session_req_done(h2_proxy_session *session, request_rec *r,
                             apr_status_t status, int touched)
{
    request_done(session->user_data, r, status, touched);
}
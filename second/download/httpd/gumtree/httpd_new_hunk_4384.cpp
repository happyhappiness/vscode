                      r->the_request);
        status = submit_stream(session, stream);
    }
    return status;
}

static void stream_resume(h2_proxy_stream *stream)
{
    h2_proxy_session *session = stream->session;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  "h2_proxy_stream(%s-%d): resuming", 
                  session->id, stream->id);
    stream->suspended = 0;
    h2_proxy_iq_remove(session->suspended, stream->id);
    nghttp2_session_resume_data(session->ngh2, stream->id);
    dispatch_event(session, H2_PROXYS_EV_STREAM_RESUMED, 0, NULL);
}

static apr_status_t check_suspended(h2_proxy_session *session)
{
    h2_proxy_stream *stream;
    int i, stream_id;
    apr_status_t status;
    
    for (i = 0; i < session->suspended->nelts; ++i) {
        stream_id = session->suspended->elts[i];
        stream = nghttp2_session_get_stream_user_data(session->ngh2, stream_id);
        if (stream) {
            if (stream->waiting_on_100 || stream->waiting_on_ping) {
                status = APR_EAGAIN;
            }
            else {
                status = ap_get_brigade(stream->r->input_filters, stream->input,
                                        AP_MODE_READBYTES, APR_NONBLOCK_READ,
                                        APR_BUCKET_BUFF_SIZE);
            }
            if (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(stream->input)) {
                stream_resume(stream);
                check_suspended(session);
                return APR_SUCCESS;
            }
            else if (status != APR_SUCCESS && !APR_STATUS_IS_EAGAIN(status)) {
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, session->c, 
                              APLOGNO(03382) "h2_proxy_stream(%s-%d): check input", 
                              session->id, stream_id);
                stream_resume(stream);
                check_suspended(session);
                return APR_SUCCESS;
            }
        }
        else {
            /* gone? */
            h2_proxy_iq_remove(session->suspended, stream_id);
            check_suspended(session);
            return APR_SUCCESS;
        }
    }
    return APR_EAGAIN;
}

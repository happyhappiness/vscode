                          "h2_proxy_session(%s): unknown event %d", 
                          session->id, ev);
            break;
    }
}

apr_status_t h2_proxy_session_process(h2_proxy_session *session)
{
    apr_status_t status;
    int have_written = 0, have_read = 0;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 

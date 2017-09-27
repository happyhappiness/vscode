        nghttp2_option_del(option);
        nghttp2_session_callbacks_del(cbs);

        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03362)
                      "setup session for %s", p_conn->hostname);
    }
    return p_conn->data;
}

static apr_status_t session_start(h2_proxy_session *session) 
{
    nghttp2_settings_entry settings[2];

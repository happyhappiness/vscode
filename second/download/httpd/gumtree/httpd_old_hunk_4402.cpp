                     (long)session->frames_sent);
    }
    ++session->frames_sent;
    return 0;
}

#define NGH2_SET_CALLBACK(callbacks, name, fn)\
nghttp2_session_callbacks_set_##name##_callback(callbacks, fn)

static apr_status_t init_callbacks(conn_rec *c, nghttp2_session_callbacks **pcb)
{
    int rv = nghttp2_session_callbacks_new(pcb);

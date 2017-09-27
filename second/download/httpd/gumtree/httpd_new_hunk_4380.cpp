                    }
                }
            }
            apr_bucket_delete(b);
        }

        stream->data_sent += readlen;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, stream->r, APLOGNO(03468) 
                      "h2_proxy_stream(%d): request DATA %ld, %ld"
                      " total, flags=%d", 
                      stream->id, (long)readlen, (long)stream->data_sent,
                      (int)*data_flags);
        return readlen;
    }
    else if (APR_STATUS_IS_EAGAIN(status)) {
        /* suspended stream, needs to be re-awakened */
        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, status, stream->r, 
                      "h2_proxy_stream(%s-%d): suspending", 
                      stream->session->id, stream_id);
        stream->suspended = 1;
        h2_proxy_iq_add(stream->session->suspended, stream->id, NULL, NULL);
        return NGHTTP2_ERR_DEFERRED;
    }
    else {
        nghttp2_submit_rst_stream(ngh2, NGHTTP2_FLAG_NONE, 
                                  stream_id, NGHTTP2_STREAM_CLOSED);
        return NGHTTP2_ERR_STREAM_CLOSING;
    }
}

#ifdef H2_NG2_INVALID_HEADER_CB
static int on_invalid_header_cb(nghttp2_session *ngh2, 
                                const nghttp2_frame *frame, 
                                const uint8_t *name, size_t namelen, 
                                const uint8_t *value, size_t valuelen, 
                                uint8_t flags, void *user_data)
{
    h2_proxy_session *session = user_data;
    if (APLOGcdebug(session->c)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03469)
                      "h2_proxy_session(%s-%d): denying stream with invalid header "
                      "'%s: %s'", session->id, (int)frame->hd.stream_id,
                      apr_pstrndup(session->pool, (const char *)name, namelen),
                      apr_pstrndup(session->pool, (const char *)value, valuelen));
    }
    return nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE,
                                     frame->hd.stream_id, 
                                     NGHTTP2_PROTOCOL_ERROR);
}
#endif

h2_proxy_session *h2_proxy_session_setup(const char *id, proxy_conn_rec *p_conn,
                                         proxy_server_conf *conf,
                                         int h2_front, 
                                         unsigned char window_bits_connection,
                                         unsigned char window_bits_stream,
                                         h2_proxy_request_done *done)
{
    if (!p_conn->data) {
        apr_pool_t *pool = p_conn->scpool;

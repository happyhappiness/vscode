                    }
                }
            }
            apr_bucket_delete(b);
        }

        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, status, stream->r, 
                      "h2_proxy_stream(%d): request body read %ld bytes, flags=%d", 
                      stream->id, (long)readlen, (int)*data_flags);
        stream->data_sent = 1;
        return readlen;
    }
    else if (APR_STATUS_IS_EAGAIN(status)) {
        /* suspended stream, needs to be re-awakened */
        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, status, stream->r, 
                      "h2_proxy_stream(%s-%d): suspending", 
                      stream->session->id, stream_id);
        stream->suspended = 1;
        h2_iq_add(stream->session->suspended, stream->id, NULL, NULL);
        return NGHTTP2_ERR_DEFERRED;
    }
    else {
        nghttp2_submit_rst_stream(ngh2, NGHTTP2_FLAG_NONE, 
                                  stream_id, NGHTTP2_STREAM_CLOSED);
        return NGHTTP2_ERR_STREAM_CLOSING;
    }
}

h2_proxy_session *h2_proxy_session_setup(const char *id, proxy_conn_rec *p_conn,
                                         proxy_server_conf *conf,
                                         unsigned char window_bits_connection,
                                         unsigned char window_bits_stream,
                                         h2_proxy_request_done *done)
{
    if (!p_conn->data) {
        apr_pool_t *pool = p_conn->scpool;

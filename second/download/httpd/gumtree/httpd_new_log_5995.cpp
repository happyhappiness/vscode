ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, stream->r, APLOGNO(03359)
                  "h2_proxy_session(%s): stream=%d, response DATA %ld, %ld"
                  " total", session->id, stream_id, (long)len,
                  (long)stream->data_received);
ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
                  "h2_stream(%ld-%d): set_response(%d)", 
                  stream->session->id, stream->id, 
                  stream->response->http_status);
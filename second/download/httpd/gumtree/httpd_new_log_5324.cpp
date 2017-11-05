ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, stream->session->c,
                  "h2_stream(%ld-%d): set_response(%d)", 
                  stream->session->id, stream->id, response->http_status);
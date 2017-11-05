ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                  "h2_stream(%ld-%d): set_response(%d)", 
                  stream->session->id, stream->id, stream->sos->response->http_status);
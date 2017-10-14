ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
                      "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d, bbin=%d", 
                      stream->session->id, stream->id, input_closed(stream),
                      stream->request->eoh, !!stream->bbin);
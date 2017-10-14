ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
                      "h2_stream(%ld-%d): scheduled %s %s://%s%s",
                      stream->session->id, stream->id,
                      stream->request->method, stream->request->scheme,
                      stream->request->authority, stream->request->path);
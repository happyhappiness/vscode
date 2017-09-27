ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      H2_STRM_MSG(stream, "schedule %s %s://%s%s chunked=%d"),
                      r->method, r->scheme, r->authority, r->path, r->chunked);
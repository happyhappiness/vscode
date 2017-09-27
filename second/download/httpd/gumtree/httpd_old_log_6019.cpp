ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, stream->m->c,
                      "h2_mplx(%ld-%d): start stream, task %s %s (%s)",
                      stream->m->id, stream->id,
                      stream->request->method, stream->request->path,
                      stream->request->authority);
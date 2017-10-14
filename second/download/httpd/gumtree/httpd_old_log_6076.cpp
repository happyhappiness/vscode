ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                  "h2_stream(%ld-%d): promised new stream %d for %s %s on %d",
                  session->id, is->id, nid,
                  push->req->method, push->req->path, is->id);
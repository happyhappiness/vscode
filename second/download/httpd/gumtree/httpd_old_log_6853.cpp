ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03076)
                  "h2_stream(%ld-%d): SERVER_PUSH %d for %s %s on %d",
                  session->id, is->id, nid,
                  push->req->method, push->req->path, is->id);
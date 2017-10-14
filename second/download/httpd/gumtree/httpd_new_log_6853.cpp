ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                  H2_STRM_LOG(APLOGNO(03076), is, "SERVER_PUSH %d for %s %s on %d"),
                  nid, push->req->method, push->req->path, is->id);
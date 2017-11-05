ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(03058)
                  "h2_request(%d): set_request_rec %s host=%s://%s%s",
                  stream->id, req->method, req->scheme, req->authority, 
                  req->path);
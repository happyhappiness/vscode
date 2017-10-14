ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(03058)
                  "h2_request(%d): rwrite %s host=%s://%s%s",
                  stream->request->id, stream->request->method, 
                  stream->request->scheme, stream->request->authority, 
                  stream->request->path);
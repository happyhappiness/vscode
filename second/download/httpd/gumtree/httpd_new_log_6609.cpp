ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, stream->r, APLOGNO(03468) 
                      "h2_proxy_stream(%d): request DATA %ld, %ld"
                      " total, flags=%d", 
                      stream->id, (long)readlen, (long)stream->data_sent,
                      (int)*data_flags);
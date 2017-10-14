ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, r->connection, APLOGNO(03197)
                  "h2_from_h1(%d): converted headers, content-length: %d"
                  ", chunked=%d",
                  from_h1->stream_id, (int)from_h1->content_length, 
                  (int)from_h1->chunked);
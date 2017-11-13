ap_log_rerror(APLOG_MARK, APLOG_DEBUG, response->http_status, r, 
                          "h2_response(%ld-%d): renegotiate forbidden, cause: %s",
                          (long)r->connection->id, stream_id, cause);
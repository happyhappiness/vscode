ap_log_perror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, pool,
                              APLOGNO(02955) "h2_response(%d): invalid header[%d] '%s'",
                              response->stream_id, i, (char*)hline);
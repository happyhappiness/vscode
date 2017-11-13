ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EINVAL, r->connection,
                      APLOGNO(02915) 
                      "h2_from_h1(%d): unable to create resp_head",
                      from_h1->stream_id);
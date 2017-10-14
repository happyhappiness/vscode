ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, session->c,
                  APLOGNO(02918) 
                  "h2_session: stream(%ld-%d): unable to create",
                  session->id, stream_id);
ap_log_perror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, stream_pool,
                      APLOGNO(02941) "h2_task(%ld-%d): create stream task", 
                      session_id, stream_id);
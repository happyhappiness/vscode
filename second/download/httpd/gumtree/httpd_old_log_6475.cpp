ap_log_perror(APLOG_MARK, LOG_LEVEL, 0, to->p, APLOGNO(03205)
                              "h2_util_move: %s, passed bucket(same bucket_alloc) "
                              "%ld-%ld, type=%s",
                              msg, (long)b->start, (long)b->length, 
                              APR_BUCKET_IS_METADATA(b)? 
                              (APR_BUCKET_IS_EOS(b)? "EOS": 
                               (APR_BUCKET_IS_FLUSH(b)? "FLUSH" : "META")) : 
                              (APR_BUCKET_IS_FILE(b)? "FILE" : "DATA"));
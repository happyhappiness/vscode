                /* both brigades use the same bucket_alloc and auto-cleanups
                 * have the same life time. It's therefore safe to just move
                 * directly. */
                APR_BUCKET_REMOVE(b);
                APR_BRIGADE_INSERT_TAIL(to, b);
#if LOG_BUCKETS
                ap_log_perror(APLOG_MARK, LOG_LEVEL, 0, to->p, APLOGNO(03205)
                              "h2_util_move: %s, passed bucket(same bucket_alloc) "
                              "%ld-%ld, type=%s",
                              msg, (long)b->start, (long)b->length, 
                              APR_BUCKET_IS_METADATA(b)? 
                              (APR_BUCKET_IS_EOS(b)? "EOS": 
                               (APR_BUCKET_IS_FLUSH(b)? "FLUSH" : "META")) : 

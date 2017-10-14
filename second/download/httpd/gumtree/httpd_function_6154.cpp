apr_status_t h2_util_move(apr_bucket_brigade *to, apr_bucket_brigade *from, 
                          apr_off_t maxlen, int *pfile_handles_allowed, 
                          const char *msg)
{
    apr_status_t status = APR_SUCCESS;
    int same_alloc;
    
    AP_DEBUG_ASSERT(to);
    AP_DEBUG_ASSERT(from);
    same_alloc = (to->bucket_alloc == from->bucket_alloc);

    if (!FILE_MOVE) {
        pfile_handles_allowed = NULL;
    }
    
    if (!APR_BRIGADE_EMPTY(from)) {
        apr_bucket *b, *end;
        
        status = last_not_included(from, maxlen, same_alloc,
                                   pfile_handles_allowed, &end);
        if (status != APR_SUCCESS) {
            return status;
        }
        
        while (!APR_BRIGADE_EMPTY(from) && status == APR_SUCCESS) {
            b = APR_BRIGADE_FIRST(from);
            if (b == end) {
                break;
            }
            
            if (same_alloc || (b->list == to->bucket_alloc)) {
                /* both brigades use the same bucket_alloc and auto-cleanups
                 * have the same life time. It's therefore safe to just move
                 * directly. */
                APR_BUCKET_REMOVE(b);
                APR_BRIGADE_INSERT_TAIL(to, b);
#if LOG_BUCKETS
                ap_log_perror(APLOG_MARK, LOG_LEVEL, 0, to->p,
                              "h2_util_move: %s, passed bucket(same bucket_alloc) "
                              "%ld-%ld, type=%s",
                              msg, (long)b->start, (long)b->length, 
                              APR_BUCKET_IS_METADATA(b)? 
                              (APR_BUCKET_IS_EOS(b)? "EOS": 
                               (APR_BUCKET_IS_FLUSH(b)? "FLUSH" : "META")) : 
                              (APR_BUCKET_IS_FILE(b)? "FILE" : "DATA"));
#endif
            }
            else if (DEEP_COPY) {
                /* we have not managed the magic of passing buckets from
                 * one thread to another. Any attempts result in
                 * cleanup of pools scrambling memory.
                 */
                if (APR_BUCKET_IS_METADATA(b)) {
                    if (APR_BUCKET_IS_EOS(b)) {
                        APR_BRIGADE_INSERT_TAIL(to, apr_bucket_eos_create(to->bucket_alloc));
                    }
                    else if (APR_BUCKET_IS_FLUSH(b)) {
                        APR_BRIGADE_INSERT_TAIL(to, apr_bucket_flush_create(to->bucket_alloc));
                    }
                    else {
                        /* ignore */
                    }
                }
                else if (pfile_handles_allowed 
                         && *pfile_handles_allowed > 0 
                         && APR_BUCKET_IS_FILE(b)) {
                    /* We do not want to read files when passing buckets, if
                     * we can avoid it. However, what we've come up so far
                     * is not working corrently, resulting either in crashes or
                     * too many open file descriptors.
                     */
                    apr_bucket_file *f = (apr_bucket_file *)b->data;
                    apr_file_t *fd = f->fd;
                    int setaside = (f->readpool != to->p);
#if LOG_BUCKETS
                    ap_log_perror(APLOG_MARK, LOG_LEVEL, 0, to->p,
                                  "h2_util_move: %s, moving FILE bucket %ld-%ld "
                                  "from=%lx(p=%lx) to=%lx(p=%lx), setaside=%d",
                                  msg, (long)b->start, (long)b->length, 
                                  (long)from, (long)from->p, 
                                  (long)to, (long)to->p, setaside);
#endif
                    if (setaside) {
                        status = apr_file_setaside(&fd, fd, to->p);
                        if (status != APR_SUCCESS) {
                            ap_log_perror(APLOG_MARK, APLOG_ERR, status, to->p,
                                          APLOGNO(02947) "h2_util: %s, setaside FILE", 
                                          msg);
                            return status;
                        }
                    }
                    apr_brigade_insert_file(to, fd, b->start, b->length, 
                                            to->p);
                    --(*pfile_handles_allowed);
                }
                else {
                    const char *data;
                    apr_size_t len;
                    status = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
                    if (status == APR_SUCCESS && len > 0) {
                        status = apr_brigade_write(to, NULL, NULL, data, len);
#if LOG_BUCKETS
                        ap_log_perror(APLOG_MARK, LOG_LEVEL, 0, to->p,
                                      "h2_util_move: %s, copied bucket %ld-%ld "
                                      "from=%lx(p=%lx) to=%lx(p=%lx)",
                                      msg, (long)b->start, (long)b->length, 
                                      (long)from, (long)from->p, 
                                      (long)to, (long)to->p);
#endif
                    }
                }
                apr_bucket_delete(b);
            }
            else {
                apr_bucket_setaside(b, to->p);
                APR_BUCKET_REMOVE(b);
                APR_BRIGADE_INSERT_TAIL(to, b);
#if LOG_BUCKETS
                ap_log_perror(APLOG_MARK, LOG_LEVEL, 0, to->p,
                              "h2_util_move: %s, passed setaside bucket %ld-%ld "
                              "from=%lx(p=%lx) to=%lx(p=%lx)",
                              msg, (long)b->start, (long)b->length, 
                              (long)from, (long)from->p, 
                              (long)to, (long)to->p);
#endif
            }
        }
    }
    
    return status;
}
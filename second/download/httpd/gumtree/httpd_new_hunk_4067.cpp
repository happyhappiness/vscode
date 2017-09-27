                 * cleanup of pools scrambling memory.
                 */
                if (APR_BUCKET_IS_METADATA(b)) {
                    if (APR_BUCKET_IS_EOS(b)) {
                        APR_BRIGADE_INSERT_TAIL(to, apr_bucket_eos_create(to->bucket_alloc));
                    }
                    else {
                        /* ignore */
                    }
                }
                else if (pfile_buckets_allowed 
                         && *pfile_buckets_allowed > 0 
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
                    ap_log_perror(APLOG_MARK, LOG_LEVEL, 0, to->p, APLOGNO(03206)
                                  "h2_util_move: %s, moving FILE bucket %ld-%ld "
                                  "from=%lx(p=%lx) to=%lx(p=%lx), setaside=%d",
                                  msg, (long)b->start, (long)b->length, 
                                  (long)from, (long)from->p, 
                                  (long)to, (long)to->p, setaside);
#endif

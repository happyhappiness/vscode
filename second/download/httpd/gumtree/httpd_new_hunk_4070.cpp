                    const char *data;
                    apr_size_t len;
                    status = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
                    if (status == APR_SUCCESS && len > 0) {
                        status = apr_brigade_write(to, NULL, NULL, data, len);
#if LOG_BUCKETS                        
                        ap_log_perror(APLOG_MARK, LOG_LEVEL, 0, to->p, APLOGNO(03209)
                                      "h2_util_copy: %s, copied bucket %ld-%ld "
                                      "from=%lx(p=%lx) to=%lx(p=%lx)",
                                      msg, (long)b->start, (long)b->length, 
                                      (long)from, (long)from->p, 
                                      (long)to, (long)to->p);
#endif

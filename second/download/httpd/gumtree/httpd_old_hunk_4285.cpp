 */
apr_status_t h2_util_bb_readx(apr_bucket_brigade *bb, 
                              h2_util_pass_cb *cb, void *ctx, 
                              apr_off_t *plen, int *peos);

/**
 * Logs the bucket brigade (which bucket types with what length)
 * to the log at the given level.
 * @param c the connection to log for
 * @param stream_id the stream identifier this brigade belongs to
 * @param level the log level (as in APLOG_*)
 * @param tag a short message text about the context
 * @param bb the brigade to log
 */
void h2_util_bb_log(conn_rec *c, int stream_id, int level, 
                    const char *tag, apr_bucket_brigade *bb);

/**
 * Transfer buckets from one brigade to another with a limit on the 
 * maximum amount of bytes transfered. Sets aside the buckets to
 * pool p.
 * @param to   brigade to transfer buckets to
 * @param from brigades to remove buckets from
 * @param p    pool that buckets should be setaside to
 * @param plen maximum bytes to transfer, actual bytes transferred
 * @param peos if an EOS bucket was transferred
 */
apr_status_t h2_ltransfer_brigade(apr_bucket_brigade *to,
                                  apr_bucket_brigade *from, 
                                  apr_pool_t *p,
                                  apr_off_t *plen,
                                  int *peos);

/**
 * Transfer all buckets from one brigade to another. Sets aside the buckets to
 * pool p.
 * @param to   brigade to transfer buckets to
 * @param from brigades to remove buckets from
 * @param p    pool that buckets should be setaside to
 */
apr_status_t h2_transfer_brigade(apr_bucket_brigade *to,
                                 apr_bucket_brigade *from, 
                                 apr_pool_t *p);

/**
 * Transfer buckets from one brigade to another with a limit on the 
 * maximum amount of bytes transfered. Does no setaside magic, lifetime
 * of brigades must fit. 
 * @param to   brigade to transfer buckets to

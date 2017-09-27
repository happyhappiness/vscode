            if (b->length > remain) {
                apr_bucket_split(b, remain);
                if (io->slen == 0) {
                    /* complete write_size bucket, append unchanged */
                    APR_BUCKET_REMOVE(b);
                    APR_BRIGADE_INSERT_TAIL(io->output, b);
#if LOG_SCRATCH
                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, io->c, APLOGNO(03391)
                                  "h2_conn_io(%ld): pass bucket(%ld)", 
                                  io->c->id, (long)b->length);
#endif
                    continue;
                }
            }
            else {
                /* bucket fits in remain, copy to scratch */
                status = read_to_scratch(io, b);

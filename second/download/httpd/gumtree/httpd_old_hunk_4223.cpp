    ap_log_cerror(APLOG_MARK, level, 0, c, "bb_dump(%ld-%d)-%s: %s", 
                  c->id, stream_id, tag, line);

}

apr_status_t h2_conn_io_init(h2_conn_io *io, conn_rec *c, 
                             const h2_config *cfg, 
                             apr_pool_t *pool)
{
    io->c             = c;
    io->output        = apr_brigade_create(pool, c->bucket_alloc);
    io->buflen        = 0;
    io->is_tls        = h2_h2_is_tls(c);
    io->buffer_output = io->is_tls;
    
    if (io->buffer_output) {
        io->bufsize = WRITE_BUFFER_SIZE;
        io->buffer = apr_pcalloc(pool, io->bufsize);
    }
    else {
        io->bufsize = 0;
    }
    
    if (io->is_tls) {
        /* This is what we start with, 
         * see https://issues.apache.org/jira/browse/TS-2503 
         */
        io->warmup_size    = h2_config_geti64(cfg, H2_CONF_TLS_WARMUP_SIZE);
        io->cooldown_usecs = (h2_config_geti(cfg, H2_CONF_TLS_COOLDOWN_SECS) 
                              * APR_USEC_PER_SEC);
        io->write_size     = WRITE_SIZE_INITIAL; 
    }
    else {
        io->warmup_size    = 0;
        io->cooldown_usecs = 0;
        io->write_size     = io->bufsize;
    }

    if (APLOGctrace1(c)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c,
                      "h2_conn_io(%ld): init, buffering=%d, warmup_size=%ld, "
                      "cd_secs=%f", io->c->id, io->buffer_output, 

/* Calculated like this: max TLS record size 16*1024
 *   - 40 (IP) - 20 (TCP) - 40 (TCP options) 
 *    - TLS overhead (60-100) 
 * which seems to create less TCP packets overall
 */
#define WRITE_SIZE_MAX        (TLS_DATA_MAX - 100) 
#define WRITE_BUFFER_SIZE     (5*WRITE_SIZE_MAX)


static void h2_conn_io_bb_log(conn_rec *c, int stream_id, int level, 
                              const char *tag, apr_bucket_brigade *bb)
{
    char buffer[16 * 1024];
    const char *line = "(null)";
    apr_size_t bmax = sizeof(buffer)/sizeof(buffer[0]);
    int off = 0;
    apr_bucket *b;
    
    if (bb) {
        memset(buffer, 0, bmax--);
        for (b = APR_BRIGADE_FIRST(bb); 
             bmax && (b != APR_BRIGADE_SENTINEL(bb));
             b = APR_BUCKET_NEXT(b)) {
            
            if (APR_BUCKET_IS_METADATA(b)) {
                if (APR_BUCKET_IS_EOS(b)) {
                    off += apr_snprintf(buffer+off, bmax-off, "eos ");
                }
                else if (APR_BUCKET_IS_FLUSH(b)) {
                    off += apr_snprintf(buffer+off, bmax-off, "flush ");
                }
                else if (AP_BUCKET_IS_EOR(b)) {
                    off += apr_snprintf(buffer+off, bmax-off, "eor ");
                }
                else if (H2_BUCKET_IS_H2EOC(b)) {
                    off += apr_snprintf(buffer+off, bmax-off, "h2eoc ");
                }
                else if (H2_BUCKET_IS_H2EOS(b)) {
                    off += apr_snprintf(buffer+off, bmax-off, "h2eos ");
                }
                else {
                    off += apr_snprintf(buffer+off, bmax-off, "meta(unknown) ");
                }
            }
            else {
                const char *btype = "data";
                if (APR_BUCKET_IS_FILE(b)) {
                    btype = "file";
                }
                else if (APR_BUCKET_IS_PIPE(b)) {
                    btype = "pipe";
                }
                else if (APR_BUCKET_IS_SOCKET(b)) {
                    btype = "socket";
                }
                else if (APR_BUCKET_IS_HEAP(b)) {
                    btype = "heap";
                }
                else if (APR_BUCKET_IS_TRANSIENT(b)) {
                    btype = "transient";
                }
                else if (APR_BUCKET_IS_IMMORTAL(b)) {
                    btype = "immortal";
                }
#if APR_HAS_MMAP
                else if (APR_BUCKET_IS_MMAP(b)) {
                    btype = "mmap";
                }
#endif
                else if (APR_BUCKET_IS_POOL(b)) {
                    btype = "pool";
                }
                
                off += apr_snprintf(buffer+off, bmax-off, "%s[%ld] ", 
                                    btype, 
                                    (long)(b->length == ((apr_size_t)-1)? 
                                           -1 : b->length));
            }
        }
        line = *buffer? buffer : "(empty)";
    }
    /* Intentional no APLOGNO */
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
                      (long)io->warmup_size,
                      ((float)io->cooldown_usecs/APR_USEC_PER_SEC));
    }

    return APR_SUCCESS;
}

int h2_conn_io_is_buffered(h2_conn_io *io)
{
    return io->bufsize > 0;
}

typedef struct {
    conn_rec *c;
    h2_conn_io *io;
} pass_out_ctx;

static apr_status_t pass_out(apr_bucket_brigade *bb, void *ctx) 
{
    pass_out_ctx *pctx = ctx;
    conn_rec *c = pctx->c;
    apr_status_t status;
    apr_off_t bblen;
    
    if (APR_BRIGADE_EMPTY(bb)) {
        return APR_SUCCESS;
    }
    
    ap_update_child_status_from_conn(c->sbh, SERVER_BUSY_WRITE, c);
    apr_brigade_length(bb, 0, &bblen);
    h2_conn_io_bb_log(c, 0, APLOG_TRACE2, "master conn pass", bb);
    status = ap_pass_brigade(c->output_filters, bb);
    if (status == APR_SUCCESS && pctx->io) {
        pctx->io->bytes_written += (apr_size_t)bblen;
        pctx->io->last_write = apr_time_now();
    }
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03044)
                      "h2_conn_io(%ld): pass_out brigade %ld bytes",
                      c->id, (long)bblen);
    }
    apr_brigade_cleanup(bb);
    return status;
}

/* Bring the current buffer content into the output brigade, appropriately
 * chunked.
 */
static apr_status_t bucketeer_buffer(h2_conn_io *io)
{
    const char *data = io->buffer;
    apr_size_t remaining = io->buflen;
    apr_bucket *b;
    int bcount, i;

    if (io->write_size > WRITE_SIZE_INITIAL 
        && (io->cooldown_usecs > 0)
        && (apr_time_now() - io->last_write) >= io->cooldown_usecs) {
        /* long time not written, reset write size */
        io->write_size = WRITE_SIZE_INITIAL;
        io->bytes_written = 0;
        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c,
                      "h2_conn_io(%ld): timeout write size reset to %ld", 
                      (long)io->c->id, (long)io->write_size);
    }
    else if (io->write_size < WRITE_SIZE_MAX 
             && io->bytes_written >= io->warmup_size) {
        /* connection is hot, use max size */
        io->write_size = WRITE_SIZE_MAX;
        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, io->c,
                      "h2_conn_io(%ld): threshold reached, write size now %ld", 
                      (long)io->c->id, (long)io->write_size);
    }
    
    bcount = (int)(remaining / io->write_size);
    for (i = 0; i < bcount; ++i) {
        b = apr_bucket_transient_create(data, io->write_size, 
                                        io->output->bucket_alloc);

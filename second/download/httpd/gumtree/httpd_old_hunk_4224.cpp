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

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
                                       apr_off_t readbytes)
{
    h2_task *task;
    apr_status_t status = APR_SUCCESS;
    apr_bucket *b, *next;
    apr_off_t bblen;
    apr_size_t rmax;
    
    task = h2_ctx_cget_task(f->c);
    ap_assert(task);
    rmax = ((readbytes <= APR_SIZE_MAX)? (apr_size_t)readbytes : APR_SIZE_MAX);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                  "h2_slave_in(%s): read, mode=%d, block=%d, readbytes=%ld", 
                  task->id, mode, block, (long)readbytes);
    
    if (mode == AP_MODE_INIT) {
        return ap_get_brigade(f->c->input_filters, bb, mode, block, readbytes);
    }
    
    if (f->c->aborted) {

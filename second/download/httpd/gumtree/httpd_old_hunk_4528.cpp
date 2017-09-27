                                  apr_off_t readbytes)
{
    h2_task *task = f->ctx;
    request_rec *r = f->r;
    apr_status_t status = APR_SUCCESS;
    apr_bucket *b, *next;

    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, f->r,
                  "h2_task(%s): request filter, exp=%d", task->id, r->expecting_100);
    if (!task->request->chunked) {
        status = ap_get_brigade(f->next, bb, mode, block, readbytes);
        /* pipe data through, just take care of trailers */

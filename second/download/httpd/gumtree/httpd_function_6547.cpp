static apr_status_t status_event(void *ctx, h2_bucket_event event, 
                                 apr_bucket *b)
{
    h2_task *task = ctx;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, task->c->master, 
                  "status_event(%s): %d", task->id, event);
    switch (event) {
        case H2_BUCKET_EV_BEFORE_MASTER_SEND:
            h2_status_insert(task, b);
            break;
        default:
            break;
    }
    return APR_SUCCESS;
}
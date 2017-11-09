static apr_status_t ngn_done_task(h2_ngn_shed *shed, h2_req_engine *ngn, 
                                  h2_task *task, int waslive, int aborted)
{
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, shed->c, APLOGNO(03400)
                  "h2_ngn_shed(%ld): task %s %s by %s", 
                  shed->c->id, task->id, aborted? "aborted":"done", ngn->id);
    ngn->no_finished++;
    if (waslive) ngn->no_live--;
    ngn->no_assigned--;
    task->assigned = NULL;
    
    return APR_SUCCESS;
}
apr_status_t h2_ngn_shed_done_task(h2_ngn_shed *shed, 
                                    struct h2_req_engine *ngn, h2_task *task)
{
    return ngn_done_task(shed, ngn, task, 1, 0);
}
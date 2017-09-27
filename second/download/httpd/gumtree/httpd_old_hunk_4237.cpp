{
    return ngn->shed;
}

void h2_ngn_shed_abort(h2_ngn_shed *shed)
{
    shed->aborted = 1;
}

static void ngn_add_task(h2_req_engine *ngn, h2_task *task)
{
    h2_ngn_entry *entry = apr_pcalloc(task->pool, sizeof(*entry));

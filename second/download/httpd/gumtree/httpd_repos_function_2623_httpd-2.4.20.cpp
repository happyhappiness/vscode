static void ngn_add_task(h2_req_engine *ngn, h2_task *task)
{
    h2_ngn_entry *entry = apr_pcalloc(task->pool, sizeof(*entry));
    APR_RING_ELEM_INIT(entry, link);
    entry->task = task;
    H2_REQ_ENTRIES_INSERT_TAIL(&ngn->entries, entry);
}
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, shed->c, APLOGNO(03394)
                  "h2_ngn_shed(%ld): abort", shed->c->id);
    shed->aborted = 1;
}

static void ngn_add_task(h2_req_engine *ngn, h2_task *task, request_rec *r)
{
    h2_ngn_entry *entry = apr_pcalloc(task->pool, sizeof(*entry));
    APR_RING_ELEM_INIT(entry, link);
    entry->task = task;
    entry->r = r;
    H2_REQ_ENTRIES_INSERT_TAIL(&ngn->entries, entry);
}


apr_status_t h2_ngn_shed_push_request(h2_ngn_shed *shed, const char *ngn_type, 
                                      request_rec *r, 
                                      http2_req_engine_init *einit) 
{
    h2_req_engine *ngn;
    h2_task *task = h2_ctx_rget_task(r);

    ap_assert(task);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, shed->c,
                  "h2_ngn_shed(%ld): PUSHing request (task=%s)", shed->c->id, 
                  task->id);
    if (task->request->serialize) {
        /* Max compatibility, deny processing of this */
        return APR_EOF;
    }
    
    if (task->assigned) {
        --task->assigned->no_assigned;
        --task->assigned->no_live;
        task->assigned = NULL;
    }
    
    ngn = apr_hash_get(shed->ngns, ngn_type, APR_HASH_KEY_STRING);
    if (ngn && !ngn->shutdown) {
        /* this task will be processed in another thread,
         * freeze any I/O for the time being. */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_ngn_shed(%ld): pushing request %s to %s", 
                      shed->c->id, task->id, ngn->id);
        if (!h2_task_has_thawed(task)) {
            h2_task_freeze(task);
        }
        ngn_add_task(ngn, task, r);
        ngn->no_assigned++;
        return APR_SUCCESS;
    }
    
    /* no existing engine or being shut down, start a new one */
    if (einit) {

apr_status_t h2_ngn_shed_pull_task(h2_ngn_shed *shed, 
                                   h2_req_engine *ngn, 
                                   apr_uint32_t capacity, 
                                   int want_shutdown,
                                   h2_task **ptask)
{   
    h2_ngn_entry *entry;
    
    AP_DEBUG_ASSERT(ngn);
    *ptask = NULL;
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, shed->c, APLOGNO(03396)
                  "h2_ngn_shed(%ld): pull task for engine %s, shutdown=%d", 
                  shed->c->id, ngn->id, want_shutdown);
    if (shed->aborted) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, shed->c, APLOGNO(03397)
                      "h2_ngn_shed(%ld): abort while pulling requests %s", 
                      shed->c->id, ngn->id);
        ngn->shutdown = 1;
        return APR_ECONNABORTED;
    }
    
    ngn->capacity = capacity;
    if (H2_REQ_ENTRIES_EMPTY(&ngn->entries)) {
        if (want_shutdown) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, shed->c,
                          "h2_ngn_shed(%ld): emtpy queue, shutdown engine %s", 
                          shed->c->id, ngn->id);
            ngn->shutdown = 1;
        }
        return ngn->shutdown? APR_EOF : APR_EAGAIN;
    }
    
    if ((entry = pop_detached(ngn))) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, entry->task->c, APLOGNO(03398)
                      "h2_ngn_shed(%ld): pulled request %s for engine %s", 
                      shed->c->id, entry->task->id, ngn->id);
        ngn->no_live++;
        *ptask = entry->task;
        entry->task->assigned = ngn;
        /* task will now run in ngn's own thread. Modules like lua
         * seem to require the correct thread set in the conn_rec.
         * See PR 59542. */
        if (entry->task->c && ngn->c) {
            entry->task->c->current_thread = ngn->c->current_thread;
        }
        if (entry->task->engine == ngn) {
            /* If an engine pushes its own base task, and then pulls
             * it back to itself again, it needs to be thawed.
             */
            h2_task_thaw(entry->task);
        }
        return APR_SUCCESS;
    }
    
    if (1) {
        h2_ngn_entry *entry = H2_REQ_ENTRIES_FIRST(&ngn->entries);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, shed->c, APLOGNO(03399)
                      "h2_ngn_shed(%ld): pull task, nothing, first task %s", 
                      shed->c->id, entry->task->id);
    }
    return APR_EAGAIN;
}
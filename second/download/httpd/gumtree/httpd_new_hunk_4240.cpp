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
                                
apr_status_t h2_ngn_shed_done_task(h2_ngn_shed *shed, 
                                    struct h2_req_engine *ngn, h2_task *task)
{

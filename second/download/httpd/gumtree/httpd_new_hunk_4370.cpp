    
    if ((entry = pop_detached(ngn))) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, entry->task->c, APLOGNO(03398)
                      "h2_ngn_shed(%ld): pulled request %s for engine %s", 
                      shed->c->id, entry->task->id, ngn->id);
        ngn->no_live++;
        *pr = entry->r;
        entry->task->assigned = ngn;
        /* task will now run in ngn's own thread. Modules like lua
         * seem to require the correct thread set in the conn_rec.
         * See PR 59542. */
        if (entry->task->c && ngn->c) {
            entry->task->c->current_thread = ngn->c->current_thread;

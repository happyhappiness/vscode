    if (ngn->done) {
        return;
    }
    
    if (!shed->aborted && !H2_REQ_ENTRIES_EMPTY(&ngn->entries)) {
        h2_ngn_entry *entry;
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, shed->c,
                      "h2_ngn_shed(%ld): exit engine %s (%s), "
                      "has still requests queued, shutdown=%d,"
                      "assigned=%ld, live=%ld, finished=%ld", 
                      shed->c->id, ngn->id, ngn->type,
                      ngn->shutdown, 
                      (long)ngn->no_assigned, (long)ngn->no_live,
                      (long)ngn->no_finished);
        for (entry = H2_REQ_ENTRIES_FIRST(&ngn->entries);
             entry != H2_REQ_ENTRIES_SENTINEL(&ngn->entries);
             entry = H2_NGN_ENTRY_NEXT(entry)) {
            h2_task *task = entry->task;
            ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, shed->c,
                          "h2_ngn_shed(%ld): engine %s has queued task %s, "
                          "frozen=%d, aborting",
                          shed->c->id, ngn->id, task->id, task->frozen);
            ngn_done_task(shed, ngn, task, 0, 1);
        }
    }
    if (!shed->aborted && (ngn->no_assigned > 1 || ngn->no_live > 1)) {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, shed->c,
                      "h2_ngn_shed(%ld): exit engine %s (%s), "
                      "assigned=%ld, live=%ld, finished=%ld", 
                      shed->c->id, ngn->id, ngn->type,
                      (long)ngn->no_assigned, (long)ngn->no_live,
                      (long)ngn->no_finished);
    }

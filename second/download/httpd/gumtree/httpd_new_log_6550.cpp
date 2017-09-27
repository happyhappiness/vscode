(1) {
        h2_ngn_entry *entry = H2_REQ_ENTRIES_FIRST(&ngn->entries);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, shed->c, APLOGNO(03399)
                      "h2_ngn_shed(%ld): pull task, nothing, first task %s", 
                      shed->c->id, entry->task->id);
    };
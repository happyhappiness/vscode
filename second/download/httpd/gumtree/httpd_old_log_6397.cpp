ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, entry->task->c,
                      "h2_ngn_shed(%ld): pulled request %s for engine %s", 
                      shed->c->id, entry->task->id, ngn->id);
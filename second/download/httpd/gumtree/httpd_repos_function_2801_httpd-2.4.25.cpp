static h2_ngn_entry *pop_detached(h2_req_engine *ngn)
{
    h2_ngn_entry *entry;
    for (entry = H2_REQ_ENTRIES_FIRST(&ngn->entries);
         entry != H2_REQ_ENTRIES_SENTINEL(&ngn->entries);
         entry = H2_NGN_ENTRY_NEXT(entry)) {
        if (h2_task_has_thawed(entry->task) 
            || (entry->task->engine == ngn)) {
            /* The task hosting this engine can always be pulled by it.
             * For other task, they need to become detached, e.g. no longer
             * assigned to another worker. */
            H2_NGN_ENTRY_REMOVE(entry);
            return entry;
        }
    }
    return NULL;
}
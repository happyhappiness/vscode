void
EventScheduler::dump(StoreEntry * sentry)
{

    ev_entry *e = tasks;

    if (last_event_ran)
        storeAppendPrintf(sentry, "Last event to run: %s\n\n", last_event_ran);

    storeAppendPrintf(sentry, "%-25s\t%-15s\t%s\t%s\n",
                      "Operation",
                      "Next Execution",
                      "Weight",
                      "Callback Valid?");

    while (e != NULL) {
        storeAppendPrintf(sentry, "%-25s\t%0.3f sec\t%5d\t %s\n",
                          e->name, e->when ? e->when - current_dtime : 0, e->weight,
                  (e->arg && e->cbdata) ? cbdataReferenceValid(e->arg) ? "yes" : "no" : "N/A");
        e = e->next;
    }
}
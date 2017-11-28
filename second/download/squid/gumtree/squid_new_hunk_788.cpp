                      "Weight",
                      "Callback Valid?");

    while (e != NULL) {
        storeAppendPrintf(sentry, "%-25s\t%0.3f sec\t%5d\t %s\n",
                          e->name, e->when ? e->when - current_dtime : 0, e->weight,
                          (e->arg && e->cbdata) ? cbdataReferenceValid(e->arg) ? "yes" : "no" : "N/A");
        e = e->next;
    }
}

bool
EventScheduler::find(EVH * func, void * arg)

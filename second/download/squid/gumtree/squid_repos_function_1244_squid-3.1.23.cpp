void
EventScheduler::cancel(EVH * func, void *arg)
{
    ev_entry **E;
    ev_entry *event;

    for (E = &tasks; (event = *E) != NULL; E = &(*E)->next) {
        if (event->func != func)
            continue;

        if (arg && event->arg != arg)
            continue;

        *E = event->next;

        delete event;

        if (arg)
            return;
        /*
         * DPW 2007-04-12
         * Since this method may now delete multiple events (when
         * arg is NULL) it no longer returns after a deletion and
         * we have a potential NULL pointer problem.  If we just
         * deleted the last event in the list then *E is now equal
         * to NULL.  We need to break here or else we'll get a NULL
         * pointer dereference in the last clause of the for loop.
         */
        if (NULL == *E)
            break;
    }

    if (arg)
        debug_trap("eventDelete: event not found");
}